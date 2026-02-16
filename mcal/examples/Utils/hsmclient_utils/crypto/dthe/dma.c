/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2024 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <dma.h>
#include <stdlib.h>
#include "Compiler.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
DMA_Handle DMA_open(uint32_t instanceId)
{
    DMA_Config *dmaCfg = NULL_PTR;

    if (instanceId < gDmaConfigNum)
    {
        dmaCfg = &gDmaConfig[instanceId];
    }

    return (dmaCfg);
}

DMA_Return_t DMA_Config_TxChannel(DMA_Handle handle, uint32_t *srcAddress, uint32_t *dstAddress, uint16_t numBlocks,
                                  uint16_t blockSize, int32_t operationType)
{
    DMA_Return_t dmaStatus       = DMA_RETURN_FAILURE;
    int32_t      dmaModuleStatus = SystemP_FAILURE;

    if (handle != NULL_PTR)
    {
        DMA_Config *config = (DMA_Config *)handle;
        if (config && config->dmaFxns && config->dmaFxns->cfgDmaTxChFxn)
        {
            dmaModuleStatus = config->dmaFxns->cfgDmaTxChFxn(config->dmaHandle, srcAddress, dstAddress, numBlocks,
                                                             blockSize, operationType);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_enableTxTransferRegion(DMA_Handle handle)
{
    DMA_Return_t dmaStatus       = DMA_RETURN_FAILURE;
    int32_t      dmaModuleStatus = SystemP_FAILURE;

    if (handle != NULL_PTR)
    {
        DMA_Config *config = (DMA_Config *)handle;

        if (config && config->dmaFxns && config->dmaFxns->enableTxTransferRegionFxn)
        {
            dmaModuleStatus = config->dmaFxns->enableTxTransferRegionFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_WaitForTxTransfer(DMA_Handle handle)
{
    DMA_Return_t dmaStatus       = DMA_RETURN_FAILURE;
    int32_t      dmaModuleStatus = SystemP_FAILURE;

    if (handle != NULL_PTR)
    {
        DMA_Config *config = (DMA_Config *)handle;

        if (config && config->dmaFxns && config->dmaFxns->waitForTxTranferFxn)
        {
            dmaModuleStatus = config->dmaFxns->waitForTxTranferFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_disableTxCh(DMA_Handle handle)
{
    DMA_Return_t dmaStatus       = DMA_RETURN_FAILURE;
    int32_t      dmaModuleStatus = SystemP_FAILURE;

    if (handle != NULL_PTR)
    {
        DMA_Config *config = (DMA_Config *)handle;

        if (config && config->dmaFxns && config->dmaFxns->enableRxTransferRegionFxn)
        {
            dmaModuleStatus = config->dmaFxns->disableTxChFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_Config_RxChannel(DMA_Handle handle, uint32_t *srcAddress, uint32_t *dstAddress, uint16_t numBlocks)
{
    DMA_Return_t dmaStatus       = DMA_RETURN_FAILURE;
    int32_t      dmaModuleStatus = SystemP_FAILURE;

    if (handle != NULL_PTR)
    {
        DMA_Config *config = (DMA_Config *)handle;
        if (config && config->dmaFxns && config->dmaFxns->cfgDmaRxChFxn)
        {
            dmaModuleStatus = config->dmaFxns->cfgDmaRxChFxn(config->dmaHandle, srcAddress, dstAddress, numBlocks);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_enableRxTransferRegion(DMA_Handle handle)
{
    DMA_Return_t dmaStatus       = DMA_RETURN_FAILURE;
    int32_t      dmaModuleStatus = SystemP_FAILURE;

    if (handle != NULL_PTR)
    {
        DMA_Config *config = (DMA_Config *)handle;

        if (config && config->dmaFxns && config->dmaFxns->enableRxTransferRegionFxn)
        {
            dmaModuleStatus = config->dmaFxns->enableRxTransferRegionFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_WaitForRxTransfer(DMA_Handle handle)
{
    DMA_Return_t dmaStatus       = DMA_RETURN_FAILURE;
    int32_t      dmaModuleStatus = SystemP_FAILURE;

    if (handle != NULL_PTR)
    {
        DMA_Config *config = (DMA_Config *)handle;

        if (config && config->dmaFxns && config->dmaFxns->waitForRxTranferFxn)
        {
            dmaModuleStatus = config->dmaFxns->waitForRxTranferFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_disableRxCh(DMA_Handle handle)
{
    DMA_Return_t dmaStatus       = DMA_RETURN_FAILURE;
    int32_t      dmaModuleStatus = SystemP_FAILURE;

    if (handle != NULL_PTR)
    {
        DMA_Config *config = (DMA_Config *)handle;

        if (config && config->dmaFxns && config->dmaFxns->enableRxTransferRegionFxn)
        {
            dmaModuleStatus = config->dmaFxns->disableRxChFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_close(DMA_Handle handle)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;

    if (handle != NULL_PTR)
    {
        handle    = NULL_PTR;
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    return (dmaStatus);
}
