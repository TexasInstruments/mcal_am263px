/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file   Fls_QSPI.c
 *
 *  \brief  QSPI  specific driver APIs implementation.
 *
 *   This file contains the driver APIs for QSPI controller.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include "Fls_Qspi.h"
#include "Fls_Brd_Nor.h"
#include "hal_stdtypes.h"
#include <mcal_hw_soc_baseaddress.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief    QSPI Command default Length in SPI words */
#define QSPI_CMD_LEN (1U)
/** \brief    QSPI Address default Length in SPI words */
#define QSPI_ADDR_LEN (1U)

/** \brief    QSPI Operation mode- Configuration or memory mapped mode */
#define QSPI_MEM_MAP_PORT_SEL_CFG_PORT     (QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT)
#define QSPI_MEM_MAP_PORT_SEL_MEM_MAP_PORT (QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT)

/** \brief    QSPI Read Type - Single, Dual or Quad */
#define QSPI_MEM_MAP_READ_TYPE_NORMAL          (QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ)
#define QSPI_MEM_MAP_READ_TYPE_DUAL            (QSPI_SPI_SETUP0_REG_READ_TYPE_DUAL_READ)
#define QSPI_MEM_MAP_READ_TYPE_NORMAL_READTYPE (QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ_TYPE)
#define QSPI_MEM_MAP_READ_TYPE_QUAD            (QSPI_SPI_SETUP0_REG_READ_TYPE_QUAD_READ)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct
{
    sint32 count;
    /**< [IN] Number of frames for this transaction */
    void  *buf;
    /**< [IN] void * to a buffer to receive/send data */
    uint32 wlen;
    /**< [IN] word length to be used for this transaction. */
    uint32 cmdRegVal;
    /**< [IN] cmd register value to be written. */
} QSPI_ConfigAccess;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Internal functions */
static Std_ReturnType Fls_Qspi_WaitIdle(QSPI_Handle handle);
static Std_ReturnType Fls_Qspi_MemMapRead(QSPI_Handle handle);
static void           Fls_Qspi_MemMapRead_sub(void);
static Std_ReturnType Fls_Qspi_ConfigRead(QSPI_Handle handle, QSPI_ConfigAccess *cfgAccess);
static Std_ReturnType Fls_Qspi_ConfigWrite(QSPI_Handle handle, QSPI_ConfigAccess *cfgAccess);
static Std_ReturnType Fls_Qspi_ProgramInstance(QSPI_Config *config);
static Std_ReturnType Fls_Qspi_ReadData(QSPI_Handle handle, uint32 *data);
static Std_ReturnType Fls_Qspi_WriteData(QSPI_Handle handle, const uint32 *data);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define FLS_START_SEC_VAR_NO_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/** \brief Driver object */
QSPI_Object Fls_QspiObjects[1];

#define FLS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/* QSPI driver configuration */

QSPI_Config Fls_QspiConfig[1] = {{&Fls_QspiObjects[0]}};

#define FLS_STOP_SEC_VAR_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT_32
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

uint32 Fls_QspiConfigNum = 1;

#define FLS_STOP_SEC_VAR_INIT_32
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define FLS_START_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/**
 *  \Function Name: Fls_hwi
 *
 *  This function check the Hardware interrupt status register. if interrupt is
 *  occured then perform the corresponding operation and this function call is
 *  in Fls_Irq.c file.
 *
 */
void Fls_hwi(void)
{
#if (STD_ON == FLS_USE_INTERRUPTS)
    uint32 intrStatus = 0U;

    intrStatus = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_STATUS_RAW_SET);

    if ((uint32)QSPI_INTR_STATUS_MASK == (uint32)(intrStatus & QSPI_INTR_STATUS_MASK))
    {
        if (Fls_DrvObj.jobType != FLS_JOB_NONE)
        {
            /* Process the job. */
            processJobs(Fls_DrvObj.jobType);

            /* disable and clear the interrupts */
            Fls_QspiIntDisable(
                (QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
            Fls_QspiIntClear((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));

            /* Check if , job is none. */
            if (Fls_DrvObj.jobType != FLS_JOB_NONE)
            {
                Fls_QspiIntEnable(
                    (QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
            }
        }
    }
    else
    {
        /* disable and clear the interrupts */
        Fls_QspiIntDisable((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
        Fls_QspiIntClear((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
    }
#endif
}

/**
 *  \Function Name: Fls_QspiHwInit
 *
 *   This function initializes the QSPI module
 *
 */
void Fls_QspiHwInit(void)
{
    QSPI_Object *qspi_Obj;
    qspi_Obj = Fls_QspiConfig[0].object;
    (void)memset(qspi_Obj, 0, sizeof(QSPI_Object));
    qspi_Obj->isOpen = FALSE;
}
/**
 *  \Function Name: Fls_QspiOpen
 *
 *   This function opens a given QSPI peripheral.
 *
 */
QSPI_Handle Fls_QspiOpen(uint32 index)
{
    Std_ReturnType retVal = E_OK;
    QSPI_Handle    handle = NULL_PTR;
    QSPI_Config   *config = (QSPI_Config *)NULL_PTR;
    QSPI_Object   *obj    = (QSPI_Object *)NULL_PTR;

    /* Check for valid index */
    if (index >= Fls_QspiConfigNum)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        config = &Fls_QspiConfig[index];
    }

    if (E_OK == retVal)
    {
        obj = config->object;
        if (TRUE == obj->isOpen)
        {
            /* Handle already opened */
            retVal = E_NOT_OK;
        }
    }

    if (E_OK == retVal)
    {
        obj->handle = (QSPI_Handle)config;
        /* Program QSPI instance according the user config */
        retVal = Fls_Qspi_ProgramInstance(config);
    }

    if (E_OK == retVal)
    {
        obj->isOpen = TRUE;
        handle      = (QSPI_Handle)config;
    }

    if (E_OK != retVal)
    {
        if (NULL_PTR != config)
        {
            Fls_QspiClose((QSPI_Handle)config);
        }
    }

    return handle;
}
/**
 *  \Function Name: Fls_QspiClose
 *
 *   Function to close a QSPI peripheral specified by the QSPI handle.
 *
 */
void Fls_QspiClose(QSPI_Handle handle)
{
    if (handle != NULL_PTR)
    {
        QSPI_Object *obj = ((QSPI_Config *)handle)->object;
        Fls_QspiIntDisable((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));

        obj->isOpen = FALSE;
    }

    return;
}
/**
 *  \Function Name: Fls_Qspi_ProgramInstance
 *
 *   Function configure QSPI Parameter such as QSPI pin and baudrate
 *
 */
static Std_ReturnType Fls_Qspi_ProgramInstance(QSPI_Config *config)
{
    Std_ReturnType retVal = E_NOT_OK;
    QSPI_Object   *obj    = config->object;
    QSPI_Handle    handle = (QSPI_Handle)config;
    uint32         regVal;

    obj->rxLines = Fls_DrvObj.Fls_Mode;

    /* Set the idle mode value */
    HW_WR_FIELD32(((uint32)(FLS_QSPI_CTRL_BASE_ADDR + QSPISYSCONFIG)), QSPI_SYSCONFIG_IDLE_MODE,
                  QSPI_SYSCONFIG_IDLE_MODE_NO_IDLE);

    regVal = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_DC_REG);

    regVal &= (uint32)(~((FLS_QSPI_FF_POL1_PHA1) << (FLS_SPI_QSPI_FF * FLS_QSPI_CS0)));
    regVal |= (FLS_QSPI_FF_POL0_PHA0 << (FLS_SPI_QSPI_FF * FLS_QSPI_CS0));

    regVal &=
        (uint32)(~((FLS_QSPI_CS_POL_ACTIVE_HIGH) << (QSPI_SPI_DC_REG_CSP0_SHIFT + (FLS_SPI_QSPI_FF * FLS_QSPI_CS0))));
    regVal |= (FLS_QSPI_CS_POL_ACTIVE_LOW << (QSPI_SPI_DC_REG_CSP0_SHIFT + (FLS_SPI_QSPI_FF * FLS_QSPI_CS0)));

    regVal &= (uint32)(~((FLS_QSPI_DATA_DELAY_3) << (QSPI_SPI_DC_REG_DD0_SHIFT + (FLS_SPI_QSPI_FF * FLS_QSPI_CS0))));
    regVal |= (FLS_QSPI_DATA_DELAY_0 << (QSPI_SPI_DC_REG_DD0_SHIFT + (FLS_SPI_QSPI_FF * FLS_QSPI_CS0)));

    retVal = Fls_Qspi_WaitIdle(handle);

    if (retVal == E_OK)
    {
        HW_WR_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_DC_REG, regVal);

        /* Enable clock and set divider value */
        if (Fls_Qspi_SetPreScaler(handle, Fls_DrvObj.flsBaudRateDiv) == E_OK)
        {
            /* Clear the interrupts and interrupt status */
            Fls_QspiIntDisable(
                (QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
            Fls_QspiIntClear((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
        }
        HW_WR_FIELD32(FLS_QSPI_CTRL_BASE_ADDR + SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                      QSPI_MEM_MAP_PORT_SEL_MEM_MAP_PORT);
    }
    return retVal;
}
/**
 *  \Function Name: Fls_Qspi_ProgramInstance
 *
 *   Function Set the QSPI clock register divider value
 *
 */
Std_ReturnType Fls_Qspi_SetPreScaler(QSPI_Handle handle, uint32 clkDividerVal)
{
    Std_ReturnType status = E_OK;

    if (handle != NULL_PTR)
    {
        uint32 regVal;

        /* Read the value of Clock control register */
        regVal = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_CLOCK_CNTRL_REG);
        /* wait for QSPI to be idle */
        status = Fls_Qspi_WaitIdle(handle);

        /* turn off QSPI data clock */
        HW_SET_FIELD32(regVal, QSPI_SPI_CLOCK_CNTRL_REG_CLKEN, QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_OFF);
        /* Set the value of QSPI clock control register */
        HW_WR_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_CLOCK_CNTRL_REG, regVal);

        /* Set the QSPI clock divider bit field value*/
        HW_SET_FIELD32(regVal, QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV, clkDividerVal);
        /* Set the value of QSPI clock control register */
        HW_WR_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_CLOCK_CNTRL_REG, regVal);

        /* Enable the QSPI data clock */
        HW_SET_FIELD32(regVal, QSPI_SPI_CLOCK_CNTRL_REG_CLKEN, QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_ON);
        /* Set the value of QSPI clock control register */
        HW_WR_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_CLOCK_CNTRL_REG, regVal);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}
/**
 *  \Function Name: Fls_Qspi_WaitIdle
 *
 *   Wait while QSPI is busy
 *
 */
static Std_ReturnType Fls_Qspi_WaitIdle(QSPI_Handle handle)
{
    Std_ReturnType status  = E_OK;
    uint32         timeout = FLS_MAX_WRITE_TIME;
    if (handle != NULL_PTR)
    {
        do
        {
            /* wait while QSPI is busy */
            if ((HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_STATUS_REG) & QSPI_SPI_STATUS_REG_BUSY_MASK) !=
                QSPI_SPI_STATUS_REG_BUSY_BUSY)
            {
                break;
            }
            timeout--;

        } while (timeout != 0U);

        if (timeout == 0U)
        {
            status = E_NOT_OK;
        }
    }
    else
    {
        status = E_NOT_OK;
    }

    return status;
}

/**
 *  \Function Name: Fls_QspiIntEnable
 *
 *   This function is used to enable word or frame complete interrupt
 *
 */
void Fls_QspiIntEnable(uint32 intFlag)
{
    uint32 regVal;
    regVal  = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_STATUS_RAW_SET);
    regVal |= (QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_ENABLE << 1) | QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_ENABLE;
    HW_WR_REG32((FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_STATUS_RAW_SET), regVal);
    regVal  = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_ENABLE_SET_REG);
    regVal |= intFlag;
    HW_WR_REG32((FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_ENABLE_SET_REG), regVal);
}
/**
 *  \Function Name: Fls_QspiIntDisable
 *
 *   This function is used to disable word or frame complete interrupt
 *
 */
void Fls_QspiIntDisable(uint32 intFlag)
{
    uint32 regVal;
    regVal  = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_ENABLE_CLEAR_REG);
    regVal |= intFlag;
    HW_WR_REG32((FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_ENABLE_CLEAR_REG), regVal);
}
/**
 *  \Function Name: Fls_QspiIntClear
 *
 *   This function is used to clear word or frame complete interrupt
 *
 */
void Fls_QspiIntClear(uint32 intFlag)
{
    uint32 regVal;

    regVal  = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_STATUS_ENABLED_CLEAR);
    regVal |= intFlag;
    HW_WR_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_STATUS_ENABLED_CLEAR, regVal);
    HW_WR_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTC_EOI_REG, QSPI_INTC_EOI_REG_EOI_VECTOR_RESETVAL);
}
/**
 *  \Function Name: Fls_Qspi_WriteData
 *
 *   This function is used to Write the Data to QSPI DATA register
 *
 */
static Std_ReturnType Fls_Qspi_WriteData(QSPI_Handle handle, const uint32 *data)
{
    Std_ReturnType status = E_OK;
    const uint32  *pData;
    pData = data;

    if (handle != NULL_PTR)
    {
        if (pData != ((const uint32 *)NULL_PTR))
        {
            HW_WR_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_DATA_REG, (uint32)*pData);
        }
        else
        {
            status = E_NOT_OK;
        }
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}
/**
 *  \Function Name: Fls_Qspi_ReadData
 *
 *   This function is used to Read the Data from QSPI DATA register
 *
 */
static Std_ReturnType Fls_Qspi_ReadData(QSPI_Handle handle, uint32 *data)
{
    Std_ReturnType status = E_OK;
    uint32        *pData  = (uint32 *)NULL_PTR;
    pData                 = data;

    if (handle != NULL_PTR)
    {
        if (pData != ((uint32 *)NULL_PTR))
        {
            *pData = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_DATA_REG);
        }
        else
        {
            status = E_NOT_OK;
        }
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}
/**
 *  \Function Name: Fls_Qspi_TransactionInit
 *
 *   Function to initialize the QSPI_Transaction structure
 *
 */
void Fls_Qspi_TransactionInit(QSPI_Transaction *trans)
{
    if (trans != NULL_PTR)
    {
        trans->count      = 0U;
        trans->buf        = NULL_PTR;
        trans->addrOffset = 0U;
        trans->status     = SPI_TRANSFER_STARTED;
    }
}
/**
 *  \Function Name: Fls_Qspi_ParamsInit
 *
 *   Initialize data structure with defaults
 *
 */
Std_ReturnType Fls_Qspi_ParamsInit(QSPI_CmdParams *QSPI_Params)
{
    Std_ReturnType retVal = E_OK;
    if (QSPI_Params != NULL_PTR)
    {
        QSPI_Params->cmd          = FLS_QSPI_CMD_INVALID_OPCODE;
        QSPI_Params->cmdAddr      = FLS_QSPI_CMD_INVALID_ADDR;
        QSPI_Params->numAddrBytes = 3;
        QSPI_Params->txDataBuf    = NULL_PTR;
        QSPI_Params->rxDataBuf    = NULL_PTR;
        QSPI_Params->DataLen      = 0;
        retVal                    = E_OK;
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
/**
 *  \Function Name: Fls_Qspi_ConfigWrite
 *
 *   It will configure the QSPI write opearation
 *
 */
static Std_ReturnType Fls_Qspi_ConfigWrite(QSPI_Handle handle, QSPI_ConfigAccess *cfgAccess)
{
    /* Source address */
    uint8          stepCmd   = 0U;
    uint8         *srcAddr8  = (uint8 *)NULL_PTR;
    uint32        *srcAddr32 = (uint32 *)NULL_PTR;
    uint32         wordLenBytes;
    /* Data to be written */
    uint32         dataVal[4] = {0};
    Std_ReturnType status     = E_OK;

    if (cfgAccess->wlen <= (uint32)8)
    {
        srcAddr8     = (uint8 *)(cfgAccess->buf);
        wordLenBytes = (uint32)1;
    }
    else
    {
        srcAddr32    = (uint32 *)(cfgAccess->buf);
        wordLenBytes = (uint32)4;
    }

    /* Write the data into shift registers */
    while (cfgAccess->count > (sint32)0U)
    {
        stepCmd = 0U;

        dataVal[0] = (uint32)0;
        if (wordLenBytes == (uint32)1)
        {
            dataVal[0] = *srcAddr8;
            srcAddr8++;
        }
        else
        {
            dataVal[0] = *srcAddr32;
            srcAddr32++;
        }
        /* Write data to data registers */
        status = Fls_Qspi_WriteData(handle, &dataVal[0]);

        if (status == E_OK)
        {
            stepCmd++;
        }
        else
        {
            stepCmd = 0U;
            status  = E_NOT_OK;
        }

        /* Wait for the QSPI busy status */
        if ((stepCmd == 1U) && (Fls_Qspi_WaitIdle(handle) == E_OK))
        {
            stepCmd++;
            /* Write tx command to command register */
            HW_WR_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_CMD_REG, cfgAccess->cmdRegVal);
        }
        else
        {
            stepCmd = 0U;
            status  = E_NOT_OK;
        }

        /* Wait for the QSPI busy status */
        if ((stepCmd == 2U) && (Fls_Qspi_WaitIdle(handle) == E_OK))
        {
            stepCmd++;

            /* update the cmd Val reg by reading it again for next word. */
            cfgAccess->cmdRegVal = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_CMD_REG);
            /* Update the number of bytes to be transmitted */
            cfgAccess->count -= (sint32)wordLenBytes;
        }
        else
        {
            stepCmd = 0U;
            status  = E_NOT_OK;
        }
        if (stepCmd == 0U)
        {
            break;
        }
    }
    return status;
}
/**
 *  \Function Name: Fls_Qspi_ConfigRead
 *
 *   It will configure the QSPI Read opearation
 *
 */
static Std_ReturnType Fls_Qspi_ConfigRead(QSPI_Handle handle, QSPI_ConfigAccess *cfgAccess)
{
    /* Source address */
    uint8         *dstAddr8  = (uint8 *)NULL_PTR;
    uint32        *dstAddr32 = (uint32 *)NULL_PTR;
    uint32         wordLenBytes;
    /* Data to be written */
    uint32         dataVal[4U] = {0U};
    Std_ReturnType status      = E_OK;

    if (cfgAccess->wlen <= 8U)
    {
        dstAddr8     = (uint8 *)(cfgAccess->buf);
        wordLenBytes = 1U;
    }
    else
    {
        dstAddr32    = (uint32 *)(cfgAccess->buf);
        wordLenBytes = 4U;
    }

    /* Write the data into shift registers */
    while (cfgAccess->count != (sint32)0U)
    {
        /* Write tx command to command register */
        HW_WR_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_CMD_REG, cfgAccess->cmdRegVal);

        /* Wait for the QSPI busy status */
        (void)Fls_Qspi_WaitIdle(handle);

        /* Store the number of data registers needed to read data */
        status = Fls_Qspi_ReadData(handle, &dataVal[0]);
        if (status == E_OK)
        {
            if (wordLenBytes == 1U)
            {
                *dstAddr8 = (uint8)dataVal[0U];
                dstAddr8++;
            }
            else
            {
                *dstAddr32 = (uint32)dataVal[0U];
                dstAddr32++;
            }

            /* update the cmd Val reg by reading it again for next word. */
            cfgAccess->cmdRegVal = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_SPI_CMD_REG);
            /* Update the number of bytes to be transmitted */
            cfgAccess->count -= (sint32)wordLenBytes;
        }
        else
        {
            break;
        }
    }
    return status;
}
/**
 *  \Function Name: Fls_Qspi_MemMapRead
 *
 *   Function to perform reads from the flash memory.
 *
 */
static Std_ReturnType Fls_Qspi_MemMapRead(QSPI_Handle handle)
{
    /* Destination address */
    uint8         *pDst = (uint8 *)NULL_PTR;
    /* Source address */
    uint8         *pSrc = (uint8 *)NULL_PTR;
    /* Transaction length */
    uint32         count;
    /* Memory mapped command */
    uint32         mmapReadCmd;
    uintptr_t      temp_addr;
    Std_ReturnType status = E_OK;
    uint32         dummyBytes, dummyBits;

    if (handle != NULL_PTR)
    {
        QSPI_Object      *object      = ((QSPI_Config *)handle)->object;
        QSPI_Transaction *transaction = object->transaction;

        /* Extract memory map mode read command */
        mmapReadCmd = (uint32)object->readCmd;

        /* Set the number of address bytes  */
        HW_WR_FIELD32((FLS_QSPI_CTRL_BASE_ADDR + SPI_SETUP0_REG) + (FLS_QSPI_CS0 * FLS_SPI_QSPI_CS0),
                      QSPI_SPI_SETUP0_REG_NUM_A_BYTES, (object->numAddrBytes - (uint32)1));

        dummyBytes = (object->numDummyBits / (uint32)8);
        dummyBits  = (object->numDummyBits % (uint32)8);

        HW_WR_FIELD32((FLS_QSPI_CTRL_BASE_ADDR + SPI_SETUP0_REG) + (FLS_QSPI_CS0 * FLS_SPI_QSPI_CS0),
                      QSPI_SPI_SETUP0_REG_NUM_D_BITS, dummyBits);
        HW_WR_FIELD32((FLS_QSPI_CTRL_BASE_ADDR + SPI_SETUP0_REG) + (FLS_QSPI_CS0 * FLS_SPI_QSPI_CS0),
                      QSPI_SPI_SETUP0_REG_NUM_D_BYTES, dummyBytes);
        HW_WR_FIELD32((FLS_QSPI_CTRL_BASE_ADDR + SPI_SETUP0_REG) + (FLS_QSPI_CS0 * FLS_SPI_QSPI_CS0),
                      QSPI_SPI_SETUP0_REG_RCMD, mmapReadCmd);

        Fls_Qspi_MemMapRead_sub();

        temp_addr = ((uintptr_t)FLS_BASE_ADDRESS + (uintptr_t)transaction->addrOffset);
        pSrc      = ((uint8 *)(temp_addr));
        pDst      = (uint8 *)transaction->buf;
        count     = transaction->count;
        while ((count) != (uint32)0U)
        {
            *pDst = *pSrc;
            pDst++;
            pSrc++;
            count--;
        }
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

static void Fls_Qspi_MemMapRead_sub(void)
{
    if (Fls_DrvObj.Fls_Mode == (uint32)FLS_QSPI_RX_LINES_QUAD)
    {
        HW_WR_FIELD32((FLS_QSPI_CTRL_BASE_ADDR + SPI_SETUP0_REG) + (FLS_QSPI_CS0 * FLS_SPI_QSPI_CS0),
                      QSPI_SPI_SETUP0_REG_READ_TYPE, QSPI_MEM_MAP_READ_TYPE_QUAD);
    }
    else if (Fls_DrvObj.Fls_Mode == (uint32)FLS_QSPI_RX_LINES_SINGLE)
    {
        HW_WR_FIELD32((FLS_QSPI_CTRL_BASE_ADDR + SPI_SETUP0_REG) + (FLS_QSPI_CS0 * FLS_SPI_QSPI_CS0),
                      QSPI_SPI_SETUP0_REG_READ_TYPE, QSPI_MEM_MAP_READ_TYPE_NORMAL);
    }
    else if (Fls_DrvObj.Fls_Mode == (uint32)FLS_QSPI_RX_LINES_DUAL)
    {
        HW_WR_FIELD32((FLS_QSPI_CTRL_BASE_ADDR + SPI_SETUP0_REG) + (FLS_QSPI_CS0 * FLS_SPI_QSPI_CS0),
                      QSPI_SPI_SETUP0_REG_READ_TYPE, QSPI_MEM_MAP_READ_TYPE_DUAL);
    }
    else
    {
        /*Do nothing*/
    }
}

/**
 *  \Function Name: Fls_Qspi_ReadMemMapMode
 *
 *   Function to perform reads from the flash in memory mapped mode.
 *
 */
Std_ReturnType Fls_Qspi_ReadMemMapMode(QSPI_Handle handle, QSPI_Transaction *trans)
{
    Std_ReturnType status = E_OK;

    if ((handle != NULL_PTR) && (trans != NULL_PTR))
    {
        QSPI_Object *object = ((QSPI_Config *)handle)->object;
        object->transaction = trans;
        trans->status       = SPI_TRANSFER_FAILED;
        status              = Fls_Qspi_MemMapRead(handle);
        if (status == E_OK)
        {
            trans->status = SPI_TRANSFER_COMPLETED;
        }
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

/**
 *  \Function Name: Fls_Qspi_ReadCmd
 *
 *   Function to send specific commands and receive related data from flash
 *
 */
Std_ReturnType Fls_Qspi_ReadCmd(QSPI_Handle handle, QSPI_CmdParams *rdParams)
{
    Std_ReturnType status     = E_OK;
    uint32         rdData_Len = 0U;
    uint32         wrdlen     = 8U;
    if ((handle != NULL_PTR) && (rdParams != NULL_PTR))
    {
        QSPI_ConfigAccess cfgAccess = {0};
        uint32            frmLength = 0;

        HW_WR_FIELD32(FLS_QSPI_CTRL_BASE_ADDR + SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                      QSPI_MEM_MAP_PORT_SEL_CFG_PORT);

        if (rdParams->cmdAddr != FLS_QSPI_CMD_INVALID_ADDR)
        {
            /* Total transaction frame length in words (bytes) */
            frmLength = QSPI_CMD_LEN + QSPI_ADDR_LEN + (rdParams->DataLen / ((uint32)8 >> (uint32)3U));
        }
        else
        {
            /* Total transaction frame length in words (bytes) */
            frmLength = QSPI_CMD_LEN + (rdParams->DataLen / ((uint32)8 >> (uint32)3U));
        }

        /* Send the command */
        cfgAccess.buf   = (uint8 *)&rdParams->cmd;
        cfgAccess.count = QSPI_CMD_LEN;
        cfgAccess.wlen  = wrdlen;
        /* formulate the command */
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_FLEN, (frmLength - (uint32)1));
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_CSNUM, FLS_QSPI_CS0);
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_CMD, QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
#if (STD_ON == FLS_USE_INTERRUPTS)
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WIRQ, (uint32)1);
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_FIRQ, (uint32)1);
#endif
        status = Fls_Qspi_ConfigWrite(handle, &cfgAccess);

        /* Send address associated with command, if any */
        if (rdParams->cmdAddr != FLS_QSPI_CMD_INVALID_ADDR)
        {
            cfgAccess.buf   = (uint8 *)&rdParams->cmdAddr;
            cfgAccess.count = QSPI_ADDR_LEN;
            /* Number of address Bytes to bits. */
            cfgAccess.wlen = ((uint32)rdParams->numAddrBytes << (uint32)3U);
            /* Update the command register value. */
            HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
            status = Fls_Qspi_ConfigWrite(handle, &cfgAccess);
        }

        /* Send data associated with command, if any */
        if (rdParams->DataLen > rdData_Len)
        {
            cfgAccess.buf   = (uint8 *)rdParams->rxDataBuf;
            cfgAccess.count = rdParams->DataLen / ((uint32)8 >> (uint32)3U);
            cfgAccess.wlen  = wrdlen;
            /* Update the command register value. */
            HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
            HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_CMD, QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE);
            status = Fls_Qspi_ConfigRead(handle, &cfgAccess);
        }
        HW_WR_FIELD32(FLS_QSPI_CTRL_BASE_ADDR + SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                      QSPI_MEM_MAP_PORT_SEL_MEM_MAP_PORT);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

/**
 *  \Function Name: Fls_Qspi_QuadReadData
 *
 *   Function to read data from external flash
 *
 */
Std_ReturnType Fls_Qspi_QuadReadData(QSPI_Handle handle, QSPI_CmdParams *rdParams)
{
    Std_ReturnType    status     = E_OK;
    uint32            rdData_Len = 0U;
    uint32            wrdlen     = 8U;
    uint32            frmLength  = 0U;
    QSPI_Object      *object     = (QSPI_Object *)NULL_PTR;
    uint8             dummyBytes = 0U;
    QSPI_ConfigAccess cfgAccess  = {0};

    if ((handle != NULL_PTR) && (rdParams != NULL_PTR))
    {
        object     = ((QSPI_Config *)handle)->object;
        dummyBytes = (uint8)(object->numDummyBits / (uint32)8);

        HW_WR_FIELD32(FLS_QSPI_CTRL_BASE_ADDR + SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                      QSPI_MEM_MAP_PORT_SEL_CFG_PORT);

        if (rdParams->cmdAddr != FLS_QSPI_CMD_INVALID_ADDR)
        {
            /* Total transaction frame length in words (bytes) */
            frmLength =
                QSPI_CMD_LEN + QSPI_ADDR_LEN + (uint32)dummyBytes + (rdParams->DataLen / ((uint32)8 >> (uint32)3U));
        }
        else
        {
            /* Total transaction frame length in words (bytes) */
            frmLength = QSPI_CMD_LEN + (rdParams->DataLen / ((uint32)8 >> (uint32)3U));
        }

        /* Send the command */
        cfgAccess.buf   = (uint8 *)&rdParams->cmd;
        cfgAccess.count = QSPI_CMD_LEN;
        cfgAccess.wlen  = wrdlen;
        /* formulate the command */
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_FLEN, (frmLength - (uint32)1));
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_CSNUM, FLS_QSPI_CS0);
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_CMD, QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
#if (STD_ON == FLS_USE_INTERRUPTS)
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WIRQ, (uint32)1);
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_FIRQ, (uint32)1);
#endif
        status = Fls_Qspi_ConfigWrite(handle, &cfgAccess);

        /* Send address associated with command, if any */
        if (rdParams->cmdAddr != FLS_QSPI_CMD_INVALID_ADDR)
        {
            cfgAccess.buf   = (uint8 *)&rdParams->cmdAddr;
            cfgAccess.count = QSPI_ADDR_LEN;
            /* Number of address Bytes to bits. */
            cfgAccess.wlen = ((uint32)rdParams->numAddrBytes << (uint32)3U);
            /* Update the command register value. */
            HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
            status = Fls_Qspi_ConfigWrite(handle, &cfgAccess);
        }

        /* Send dummy bytes associated with the read command */
        if (dummyBytes > 0U)
        {
            cfgAccess.buf   = (uint8 *)&rdParams->cmd;
            cfgAccess.count = dummyBytes;
            cfgAccess.wlen  = dummyBytes * wrdlen;
            HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
            status = Fls_Qspi_ConfigWrite(handle, &cfgAccess);
        }

        /* Send data associated with command, if any */
        if (rdParams->DataLen > rdData_Len)
        {
            cfgAccess.buf   = (uint8 *)rdParams->rxDataBuf;
            cfgAccess.count = rdParams->DataLen / ((uint32)8 >> (uint32)3U);
            cfgAccess.wlen  = wrdlen;
            /* Update the command register value. */
            HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
            HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_CMD, QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD);
            status = Fls_Qspi_ConfigRead(handle, &cfgAccess);
        }
        HW_WR_FIELD32(FLS_QSPI_CTRL_BASE_ADDR + SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                      QSPI_MEM_MAP_PORT_SEL_MEM_MAP_PORT);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

/**
 *  \Function Name: Fls_Qspi_WriteCmd
 *
 *   Function to send specific commands and related data to flash
 *
 */
Std_ReturnType Fls_Qspi_WriteCmd(QSPI_Handle handle, QSPI_CmdParams *wrParams)
{
    Std_ReturnType status     = E_OK;
    uint32         wrData_Len = 0U;
    uint32         wrdlen     = 8U;

    if ((handle != NULL_PTR) && (wrParams != NULL_PTR))
    {
        QSPI_ConfigAccess cfgAccess = {0};
        uint32            frmLength = 0;

        HW_WR_FIELD32(FLS_QSPI_CTRL_BASE_ADDR + SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                      QSPI_MEM_MAP_PORT_SEL_CFG_PORT);

        if (wrParams->cmdAddr != FLS_QSPI_CMD_INVALID_ADDR)
        {
            /* Total transaction frame length in words (bytes) */
            frmLength = QSPI_CMD_LEN + QSPI_ADDR_LEN + (wrParams->DataLen / ((uint32)8 >> (uint32)3U));
        }
        else
        {
            /* Total transaction frame length in words (bytes) */
            frmLength = QSPI_CMD_LEN + (wrParams->DataLen / ((uint32)8 >> (uint32)3U));
        }

        /* Send the command */
        cfgAccess.buf   = (uint8 *)&wrParams->cmd;
        cfgAccess.count = QSPI_CMD_LEN;
        cfgAccess.wlen  = wrdlen;
        /* formulate the command */
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_FLEN, (frmLength - (uint32)1));
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_CSNUM, FLS_QSPI_CS0);
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_CMD, QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
#if (STD_ON == FLS_USE_INTERRUPTS)
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WIRQ, (uint32)1);
        HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_FIRQ, (uint32)1);
#endif
        status = Fls_Qspi_ConfigWrite(handle, &cfgAccess);

        /* Send address associated with command, if any */
        if (wrParams->cmdAddr != FLS_QSPI_CMD_INVALID_ADDR)
        {
            cfgAccess.buf   = (uint8 *)&wrParams->cmdAddr;
            cfgAccess.count = QSPI_ADDR_LEN;
            /* Number of address Bytes to bits. */
            cfgAccess.wlen = ((uint32)wrParams->numAddrBytes << (uint32)3U);
            /* Update the command register value. */
            HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
            status = Fls_Qspi_ConfigWrite(handle, &cfgAccess);
        }

        /* Send data associated with command, if any */
        if (wrParams->DataLen > wrData_Len)
        {
            cfgAccess.buf   = (uint8 *)wrParams->txDataBuf;
            cfgAccess.count = wrParams->DataLen / ((uint32)8 >> (uint32)3U);
            cfgAccess.wlen  = wrdlen;
            /* Update the command register value. */
            HW_SET_FIELD32(cfgAccess.cmdRegVal, QSPI_SPI_CMD_REG_WLEN, (cfgAccess.wlen - (uint32)1));
            status = Fls_Qspi_ConfigWrite(handle, &cfgAccess);
        }
        HW_WR_FIELD32(FLS_QSPI_CTRL_BASE_ADDR + SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                      QSPI_MEM_MAP_PORT_SEL_MEM_MAP_PORT);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}
/**
 *  \Function Name: Fls_Qspi_WriteCmd
 *
 *   Function to perform writes to the flash in configuration mode
 *
 */
Std_ReturnType Fls_Qspi_WriteConfigMode(QSPI_Handle handle, QSPI_Transaction *trans)
{
    Std_ReturnType status = E_OK;

    if ((handle != NULL_PTR) && (trans != NULL_PTR))
    {
        QSPI_CmdParams wrParams;
        QSPI_Object   *object = ((QSPI_Config *)handle)->object;

        wrParams.cmd          = object->writeCmd;
        wrParams.cmdAddr      = trans->addrOffset;
        wrParams.numAddrBytes = object->numAddrBytes;
        wrParams.txDataBuf    = trans->buf;
        wrParams.DataLen      = trans->count;

        status = Fls_Qspi_WriteCmd(handle, &wrParams);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

/**
 *  \Function Name: Fls_Qspi_ReadConfigMode
 *
 *   Function to perform reads from the flash in configuration mode
 *
 */
Std_ReturnType Fls_Qspi_ReadConfigMode(QSPI_Handle handle, QSPI_Transaction *trans)
{
    Std_ReturnType retVal    = E_NOT_OK;
    uint8          stepCheck = 0U;
    QSPI_CmdParams rdParams;

    if (handle != NULL_PTR)
    {
        stepCheck++;
    }

    if ((stepCheck == 1U) && (Fls_Qspi_ParamsInit(&rdParams) == E_OK))
    {
        QSPI_Object *object = ((QSPI_Config *)handle)->object;

        rdParams.cmd          = object->readCmd;
        rdParams.cmdAddr      = trans->addrOffset;
        rdParams.numAddrBytes = object->numAddrBytes;
        rdParams.rxDataBuf    = trans->buf;
        rdParams.DataLen      = trans->count;

        if (Fls_Qspi_QuadReadData(Fls_DrvObj.spiHandle, &rdParams) == E_OK)
        {
            retVal = E_OK;
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }

    return retVal;
}

/**
 *  \Function Name: Fls_IntClearDisable
 *
 *   This function is used to disable and clear Interrupt Register.
 *
 */
void Fls_IntClearDisable(void)
{
    Fls_QspiIntDisable((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
    Fls_QspiIntClear((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
}

void Fls_Interrupt_Enable(void)
{
    uint32 intrStatus = 0u;
    intrStatus        = HW_RD_REG32(FLS_QSPI_CTRL_BASE_ADDR + QSPI_INTR_STATUS_RAW_SET);
    if ((uint32)QSPI_INTR_STATUS_MASK == (uint32)(intrStatus & QSPI_INTR_STATUS_MASK))
    {
        Fls_QspiIntDisable((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));

        Fls_QspiIntClear((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
    }
    else
    {
    }
    Fls_QspiIntEnable((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
}

#define FLS_STOP_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/*******************************************************************************
 *  End of File: Fls_Qspi.c
 ******************************************************************************/
