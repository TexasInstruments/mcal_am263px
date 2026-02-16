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

/**
 *  \file     BootApp.c
 *
 *  \brief    This file contains the MCAL Bootloader
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Det.h"
#include "Fls.h"
#include "Fls_Irq.h"
#include "Fls_Brd_Nor.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Port_Cfg.h"
#include "Port.h"
/*LDRA_NOANALYSIS*/
#include "string.h"
/*LDRA_ANALYSIS*/
#include "trace.h"
#include "FlsApp_Startup.h"
#include "CacheP.h"

/* Starterware Includes */
#include "sys_vim.h"
#include "app_utils.h"
#include "soc.h"
#include "hw_ctrl_core.h"
#if defined(AM263PX_PLATFORM)
#include "app_utilsI2c.h"
#endif

#include "bootloader.h"
#include "hsmclient.h"
#include "fss.h"
#include <dthe.h>
#include <dthe_aes.h>
#include <dthe_sha.h>
#include <dma.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))

/* This macro should be (1) if sector erase application is needed to run */
#define SECTOR_ERASE (1)
/* This macro should be (1) if block erase application is needed to run */
#define BLOCK_ERASE (0)
/* This macro should be (1) if bulk/chip erase application is needed to run */
#define CHIP_ERASE (0)

/* sysconfig generated parameter QUEUE LENGTH */
#define SIPC_QUEUE_LENGTH (32u)
/* Total number of secure cores */
#define SIPC_NUM_R5_CORES (2u)

/* FSS Region used for AB SWAP*/
#define FSS_REG_1 (0x80000000UL)

/**
 * @brief
 *        Maximum size of the HSM client message queue
 *        For Streaming Secure Boot, the break up is as follows,
 *        1 start message (includes the certificate) +
 *        1 finish message +
 *        1 ELF Header Buffer update message + 1 PHT Buffer update message
 *        1024 ELF segment update messages (including the two note segments)
 *          - PT note for boot sequence info
 *          - PT note containing Random string for decryption verification
 */
#define HSM_CLIENT_MSG_QUEUE_SIZE (64U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void          FlsApp_Startup(void);
void          main_handling(void);
uint8         fls_sampleapp(void);
uint32        Fls_TestPassed;
uint16        test_forloop = 0;
uint32        Data_Size_Test;
uint32        Data_Value;
uint32        numOfSectorsOrBlocks;
uint32        CfgSectorOrBlockSize;
uint32        numofseccfg;
uint32        offset;
uint32        Total_datasize;
uint32        type_of_erase;
extern uint32 sector_or_blocksize;

/* BOOTLOADER Instance Macros */
#define CONFIG_BOOTLOADER0              (0U)
#define CONFIG_BOOTLOADER_NUM_INSTANCES (1U)
#define CONFIG_FLASH0                   (0U)

#define APP_CLIENT_ID       (0x02)
#define SEED_SIZE_IN_DWORDS (12U)

/* Bootloader boot media specific arguments */
Bootloader_FlashArgs gBootloader0Args = {
    .flashIndex     = CONFIG_FLASH0,
    .curOffset      = 0,
    .appImageOffset = 0x000C0000,
};

/* Configuration option for lockstep or standalone */
Bootloader_socCoreOpModeConfig operatingMode = {
    BOOTLOADER_OPMODE_LOCKSTEP,
    BOOTLOADER_OPMODE_LOCKSTEP,
};

/* Bootloader driver configuration */
Bootloader_Config gBootloaderConfig[CONFIG_BOOTLOADER_NUM_INSTANCES] = {
    {
        &gBootloaderFlashFxns,
        &gBootloader0Args,
        BOOTLOADER_MEDIA_FLASH,
        0,
        0,
        NULL_PTR,

        .socCoreOpMode       = (void *)&operatingMode,
        .isAppimageSigned    = FALSE,
        .disableAppImageAuth = FALSE,
        .initICSSCores       = FALSE,
        0,
    },
};

uint32_t gBootloaderConfigNum = CONFIG_BOOTLOADER_NUM_INSTANCES;

/* ----------- HwiP ----------- */
HwiP_Config gHwiConfig = {
    .intcBaseAddr = 0x50F00000u,
};

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define FLSEXAMPLE_ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))
#define DATA_SIZE_TEST          64 * 1024

#if (STD_ON == FLS_VERSION_INFO_API)
Std_VersionInfoType VersionInfo;
#endif

/* Buffer containing the known data that needs to be written to flash */
uint8 txBuf_test[DATA_SIZE_TEST] = {0};
/* Buffer containing the received data */
uint8 rxBuf_test[DATA_SIZE_TEST] = {0};

/* memory assigned for each R5x <-> HSM channel */
uint8_t gQueue_HsmToSecureHost[SIPC_NUM_R5_CORES][SIPC_QUEUE_LENGTH * SIPC_MSG_SIZE]
    __attribute__((aligned(8), section(".bss.sipc_hsm_queue_mem")));
uint8_t gQueue_SecureHostToHsm[SIPC_NUM_R5_CORES][SIPC_QUEUE_LENGTH * SIPC_MSG_SIZE]
    __attribute__((aligned(8), section(".bss.sipc_secure_host_queue_mem")));
HsmClient_t gHSMClient;

/* Queue used to store HSM client messages that need to be dispatched via SIPC */
HsmMsg_t gHsmClientMsgQueue[HSM_CLIENT_MSG_QUEUE_SIZE];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/* Input buf length*/
#define APP_CRYPTO_HMAC_SHA512_INPUT_BUF_LENGTH (9U)
/* HMAC SHA-512 length */
#define APP_CRYPTO_HMAC_SHA512_OUTPUT_LENGTH (64U)
/* HMAC-SHA512 input key length */
#define APP_CRYPTO_HMAC_SHA512_INPUT_KEY_LENGTH (64U)
/* Alignment */
#define APP_CRYPTO_HMAC_SHA512_BUF_ALIGNMENT (128U)
/* Input or output length*/
#define APP_CRYPTO_AES_CBC_128_INOUT_LENGTH (16U)
/* AES CBC IV length in bytes */
#define APP_CRYPTO_AES_CBC_128_IV_LENGTH_IN_BYTES (16U)
/* AES CBC KEY length in bytes */
#define APP_CRYPTO_AES_CBC_128_KEY_LENGTH_IN_BYTES (16U)
/* AES CBC KEY Catche alignment size */
#define APP_CRYPTO_AES_CBC_128_CATCHE_ALIGNMENT (32U)
/* DTHE Public address */
#define CSL_DTHE_PUBLIC_U_BASE (0xCE000810U)
/* DTHE Aes Public address */
#define CSL_DTHE_PUBLIC_AES_U_BASE (0xCE007000U)
/* DTHE Aes Public address */
#define CSL_DTHE_PUBLIC_SHA_U_BASE (0xCE005000U)

/* EDMA config instance */
#define CONFIG_EDMA_NUM_INSTANCES (1U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Input test buffer for hmac sha-512 computation */
static uint8_t gCryptoHmacSha512TestInputBuf[APP_CRYPTO_HMAC_SHA512_INPUT_BUF_LENGTH] = {"abcdefpra"};

/* Expected output buffer for hmac sha-512 computation */
uint8_t gCryptoHmacSha512ExpectedOutput[APP_CRYPTO_HMAC_SHA512_OUTPUT_LENGTH] = {
    0xedU, 0x5aU, 0x6fU, 0xe2U, 0x41U, 0x32U, 0xb9U, 0xfaU, 0xa7U, 0x1fU, 0x3dU, 0x3eU, 0xf0U, 0xcaU, 0x0aU, 0x42U,
    0xefU, 0x82U, 0xf8U, 0xfeU, 0x0dU, 0xf5U, 0x9fU, 0x35U, 0x1fU, 0x26U, 0xdbU, 0x10U, 0x22U, 0xc8U, 0x94U, 0x7aU,
    0x1dU, 0xeeU, 0x7aU, 0x3aU, 0xa4U, 0x91U, 0x71U, 0x8bU, 0x85U, 0xbcU, 0x4dU, 0x8aU, 0x7aU, 0xd1U, 0xadU, 0xe5U,
    0x0fU, 0xc1U, 0x87U, 0x94U, 0x6fU, 0x56U, 0x38U, 0x41U, 0x11U, 0x99U, 0xcfU, 0xe8U, 0x67U, 0x44U, 0x27U, 0xc7U};

/* Key buffer for hmac sha-512 computation */
static uint8_t gCryptoHmacSha512Key[APP_CRYPTO_HMAC_SHA512_INPUT_KEY_LENGTH] = {
    0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU,
    0x10U, 0x11U, 0x12U, 0x13U, 0x14U, 0x15U, 0x16U, 0x17U, 0x18U, 0x19U, 0x1AU, 0x1BU, 0x1CU, 0x1DU, 0x1EU, 0x1FU,
    0x20U, 0x21U, 0x22U, 0x23U, 0x24U, 0x25U, 0x26U, 0x27U, 0x28U, 0x29U, 0x2AU, 0x2BU, 0x2CU, 0x2DU, 0x2EU, 0x2FU,
    0x30U, 0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U, 0x3AU, 0x3BU, 0x3CU, 0x3DU, 0x3EU, 0x3FU};

/* Input buffer for encryption or decryption */
static uint8_t gCryptoAesCbc128PlainText[APP_CRYPTO_AES_CBC_128_INOUT_LENGTH]
    __attribute__((aligned(APP_CRYPTO_AES_CBC_128_CATCHE_ALIGNMENT))) = {
        0x98, 0x3B, 0xF6, 0xF5, 0xA6, 0xDF, 0xBC, 0xDA, 0xA1, 0x93, 0x70, 0x66, 0x6E, 0x83, 0xA9, 0x9A};

/* The AES algorithm encrypts and decrypts data in blocks of 128 bits. It can do this using 128-bit or 256-bit keys */
static uint8_t gCryptoAesCbc128Key[APP_CRYPTO_AES_CBC_128_KEY_LENGTH_IN_BYTES]
    __attribute__((aligned(APP_CRYPTO_AES_CBC_128_CATCHE_ALIGNMENT))) = {
        0x93, 0x28, 0x67, 0x64, 0xA8, 0x51, 0x46, 0x73, 0x0E, 0x64, 0x18, 0x88, 0xDB, 0x34, 0xEB, 0x47};

/* Encrypted buffer of gCryptoAesCbc128PlainText */
static uint8_t gCryptoAesCbc128CipherText[APP_CRYPTO_AES_CBC_128_INOUT_LENGTH]
    __attribute__((aligned(APP_CRYPTO_AES_CBC_128_CATCHE_ALIGNMENT))) = {
        0x28, 0x33, 0xdc, 0xc7, 0x24, 0xdc, 0x6a, 0xff, 0x5a, 0x72, 0xe4, 0x3d, 0xdf, 0xb6, 0x63, 0x35};

/* Initialization vector (IV) is an arbitrary number that can be used along with a secret key for data
 * encryption/decryption. */
static uint8_t gCryptoAesCbc128Iv[APP_CRYPTO_AES_CBC_128_IV_LENGTH_IN_BYTES]
    __attribute__((aligned(APP_CRYPTO_AES_CBC_128_CATCHE_ALIGNMENT))) = {
        0x19, 0x2D, 0x9B, 0x3A, 0xA1, 0x0B, 0xB2, 0xF7, 0x84, 0x6C, 0xCB, 0xA0, 0x08, 0x5C, 0x65, 0x7A};

/* Public context crypto dthe, aes and sha accelerators base address */
DTHE_Attrs gDTHE_Attrs[1] = {
    {
        /* crypto accelerator base address */
        .caBaseAddr = CSL_DTHE_PUBLIC_U_BASE,
        /* AES base address */
        .aesBaseAddr = CSL_DTHE_PUBLIC_AES_U_BASE,
        /* SHA base address */
        .shaBaseAddr = CSL_DTHE_PUBLIC_SHA_U_BASE,
        /* For checking dthe driver open or close */
        .isOpen = FALSE,
    },
};

DTHE_Config gDtheConfig[1] = {
    {
        &gDTHE_Attrs[0],
        0,
    },
};

DMA_Config gDmaConfig[1] = {
    {
        NULL_PTR,
        NULL_PTR,
    },
};
uint32_t gDmaConfigNum = 1;

uint32_t gDtheConfigNum = 1;

void HsmClient_config(void)
{
    SIPC_Params sipcParams;

    /* initialize parameters to default */
    SIPC_Params_init(&sipcParams);

    sipcParams.ipcQueue_eleSize_inBytes = SIPC_MSG_SIZE;
    sipcParams.ipcQueue_length          = SIPC_QUEUE_LENGTH;
    /* list the cores that will do SIPC communication with this core
     * Make sure to NOT list 'self' core in the list below
     */
    sipcParams.numCores      = 1;
    sipcParams.coreIdList[0] = CORE_INDEX_HSM;

    /* specify the priority of SIPC Notify interrupt */
    sipcParams.intrPriority = 7U;

    /* This is HSM -> R5F queue */
    sipcParams.tx_SipcQueues[CORE_INDEX_HSM]          = (uintptr_t)gQueue_SecureHostToHsm[0];
    sipcParams.rx_SipcQueues[CORE_INDEX_HSM]          = (uintptr_t)gQueue_HsmToSecureHost[0];
    sipcParams.secHostCoreId[CORE_INDEX_SEC_MASTER_0] = CORE_ID_R5FSS0_0;

    /* initialize the HsmClient module */
    HsmClient_init(&sipcParams);
    HsmClient_SecureBootQueueInit(HSM_CLIENT_MSG_QUEUE_SIZE);

    /* register a hsm client to detect bootnotify message and keyring import from HSM */
    HsmClient_register(&gHSMClient, HSM_BOOT_NOTIFY_CLIENT_ID);
}

void HsmClient_unRegister(void)
{
    /* Unregister bootnotify client */
    HsmClient_unregister(&gHSMClient, HSM_BOOT_NOTIFY_CLIENT_ID);
}

void crypto_aes_cbc_128_main(void)
{
    DTHE_AES_Return_t status;
    DTHE_Handle       aesHandle;
    DTHE_AES_Params   aesParams;
    uint32_t          aesResult[APP_CRYPTO_AES_CBC_128_INOUT_LENGTH / 4U];

    /* opens DTHe driver */
    aesHandle = DTHE_open(0);

    AppUtils_printf("[CRYPTO] DTHE AES CBC-128 example started ...\r\n");

    /* Initialize the AES Parameters */
    (void)memset((void *)&aesParams, 0, sizeof(DTHE_AES_Params));

    /* Initialize the results: We set the result to a non-zero value. */
    (void)memset((void *)&aesResult[0], 0xFF, sizeof(aesResult));

    /* Initialize the decryption parameters */
    aesParams.algoType         = DTHE_AES_CBC_MODE;
    aesParams.opType           = DTHE_AES_DECRYPT;
    aesParams.useKEKMode       = FALSE;
    aesParams.ptrKey           = (uint32_t *)&gCryptoAesCbc128Key[0];
    aesParams.keyLen           = DTHE_AES_KEY_128_SIZE;
    aesParams.ptrIV            = (uint32_t *)&gCryptoAesCbc128Iv[0];
    aesParams.ptrEncryptedData = (uint32_t *)&gCryptoAesCbc128CipherText[0];
    aesParams.dataLenBytes     = APP_CRYPTO_AES_CBC_128_INOUT_LENGTH;
    aesParams.ptrPlainTextData = (uint32_t *)&aesResult[0];

    /* opens aes driver */
    status = DTHE_AES_open(aesHandle);

    /* Decryption */
    status = DTHE_AES_execute(aesHandle, &aesParams);

    /* Comaring Aes operation result with expected result */
    if (memcmp((void *)&gCryptoAesCbc128PlainText[0], (void *)&aesResult[0], APP_CRYPTO_AES_CBC_128_INOUT_LENGTH) == 0)
    {
        status = DTHE_AES_RETURN_SUCCESS;
    }
    else
    {
        status = DTHE_AES_RETURN_FAILURE;
    }

    if (status == DTHE_AES_RETURN_SUCCESS)
    {
        /* Initialize the AES Parameters */
        (void)memset((void *)&aesParams, 0, sizeof(DTHE_AES_Params));

        /* Initialize the results: We set the result to a non-zero value. */
        (void)memset((void *)&aesResult[0], 0xFF, sizeof(aesResult));

        /* Initialize the encryption parameters */
        aesParams.algoType         = DTHE_AES_CBC_MODE;
        aesParams.opType           = DTHE_AES_ENCRYPT;
        aesParams.useKEKMode       = FALSE;
        aesParams.ptrKey           = (uint32_t *)&gCryptoAesCbc128Key[0];
        aesParams.keyLen           = DTHE_AES_KEY_128_SIZE;
        aesParams.ptrIV            = (uint32_t *)&gCryptoAesCbc128Iv[0];
        aesParams.ptrPlainTextData = (uint32_t *)&gCryptoAesCbc128PlainText[0];
        aesParams.dataLenBytes     = APP_CRYPTO_AES_CBC_128_INOUT_LENGTH;
        aesParams.ptrEncryptedData = (uint32_t *)&aesResult[0];

        /* Encryption */
        status = DTHE_AES_execute(aesHandle, &aesParams);
    }

    /* Closing aes driver */
    status = DTHE_AES_close(aesHandle);

    /* Closing DTHE driver */
    if (DTHE_RETURN_SUCCESS == DTHE_close(aesHandle))
    {
        status = DTHE_AES_RETURN_SUCCESS;
    }
    else
    {
        status = DTHE_AES_RETURN_FAILURE;
    }

    /* Comaring Aes operation result with expected result */
    if (memcmp((void *)&gCryptoAesCbc128CipherText[0], (void *)&aesResult[0], APP_CRYPTO_AES_CBC_128_INOUT_LENGTH) == 0)
    {
        AppUtils_printf("[CRYPTO] DTHE AES CBC-128 example completed!!\r\n");
        AppUtils_printf("All tests have passed!!\r\n");
    }
    else
    {
        AppUtils_printf("[CRYPTO] DTHE AES CBC-128 example failed!!\r\n");
    }
}

void crypto_hmac_sha512_main(void)
{
    DTHE_SHA_Return_t status;
    DTHE_Handle       shaHandle;
    DTHE_SHA_Params   shaParams;

    AppUtils_printf("[CRYPTO] DTHE HMAC SHA-512 example started ...\r\n");

    /* opens DTHe driver */
    shaHandle = DTHE_open(0);

    /* Opening sha driver */
    status = DTHE_SHA_open(shaHandle);

    /* Initialize the SHA Parameters */
    shaParams.algoType      = DTHE_SHA_ALGO_SHA512;
    shaParams.ptrDataBuffer = (uint32_t *)&gCryptoHmacSha512TestInputBuf[0];
    shaParams.dataLenBytes  = APP_CRYPTO_HMAC_SHA512_INPUT_BUF_LENGTH;
    shaParams.ptrKey        = (uint32_t *)&gCryptoHmacSha512Key[0];
    shaParams.keySize       = APP_CRYPTO_HMAC_SHA512_INPUT_KEY_LENGTH;

    /* Performing DTHE HMAC SHA operation */
    status = DTHE_HMACSHA_compute(shaHandle, &shaParams);

    /* Closing sha driver */
    status = DTHE_SHA_close(shaHandle);

    /* Closing DTHE driver */
    if (DTHE_RETURN_SUCCESS == DTHE_close(shaHandle))
    {
        status = DTHE_SHA_RETURN_SUCCESS;
    }
    else
    {
        status = DTHE_SHA_RETURN_FAILURE;
    }

    if (status == DTHE_SHA_RETURN_SUCCESS)
    {
        /* Comparing final HMAC SHA-512 result with expected test results*/
        if (memcmp(shaParams.digest, gCryptoHmacSha512ExpectedOutput, APP_CRYPTO_HMAC_SHA512_OUTPUT_LENGTH) != 0)
        {
            AppUtils_printf("[CRYPTO] DTHE HMAC SHA-512 example failed!!\r\n");
        }
        else
        {
            AppUtils_printf("[CRYPTO] DTHE HMAC SHA-512 example completed!!\r\n");
            AppUtils_printf("All tests have passed!!\r\n");
        }
    }
}

int main(void)
{
    FlsApp_Startup();
#if defined(AM263PX_PLATFORM)
#if defined AM263PX_R_PACKAGE || defined AM263PX_C_PACKAGE
    I2c_utilsInterruptConfig();
    Cdd_I2c_Init(NULL_PTR);
    board_flash_reset();
#endif  // #if defined AM263PX_R_PACKAGE || defined AM263PX_C_PACKAGE
#endif  // if defined(AM263PX_PLATFORM)

    AppUtils_printf("FlsApp: Sample Application - STARTS !!!\n\r");
#if (STD_ON == FLS_DMA_ENABLE)
    Cdd_Dma_Init(NULL_PTR);
#endif
#if (STD_ON == FLS_USE_INTERRUPTS)
    AppUtils_printf(APP_NAME ": Configuring Interrupt.\n\r");
#endif /* #if (STD_ON == FLS_USE_INTERRUPTS) */

#if (STD_ON == FLS_PRE_COMPILE_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - Pre Compile being used !!!\n\r");
    Fls_Init((const Fls_ConfigType *)NULL_PTR);
#else
    AppUtils_printf(APP_NAME ": Variant - Post Build being used !!!\n\r");
    Fls_Init(&Fls_Config);
#endif /* #if (STD_ON == FLS_PRE_COMPILE_VARIANT) */

#if (STD_ON == FLS_VERSION_INFO_API)
    Fls_GetVersionInfo(&VersionInfo);
    AppUtils_printf("FLS MCAL version info:%d.%d.%d\n\r", VersionInfo.sw_major_version, VersionInfo.sw_minor_version,
                    VersionInfo.sw_patch_version);
    AppUtils_printf("FLS MCAL Module/Driver:%d.%d \n\r", VersionInfo.moduleID, VersionInfo.vendorID);
#endif /* #if (STD_ON == FLS_VERSION_INFO_API) */

/* FLS driver should be free now - check */
#if (STD_ON == FLS_GET_STATUS_API)
    MemIf_StatusType status;
    status = Fls_GetStatus();
    if (status != MEMIF_IDLE)
    {
        AppUtils_printf(APP_NAME ": FLS driver is not IDLE!!\n\r");
    }
#endif /* #if ( STD_ON == FLS_GET_STATUS_API) */

    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params        bootParams;
    Bootloader_Handle        bootHandle;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    bootHandle = Bootloader_open(CONFIG_BOOTLOADER0, &bootParams);

/*  For AB SWAP the FLS_BASE_ADDRESS should be configured as 0x80000000.
    Respective MPU region should also be configured in MpuP_armv7r.c for 0x80000000.
*/
#if (FLS_BASE_ADDRESS == FSS_REG_1)
    {
        status = SystemP_FAILURE;

        if (NULL_PTR != Fls_Config_SFDP_Ptr)
        {
            uint32_t   bootret    = 0;
            FSS_Config fssConf    = {0, 0};
            fssConf.ipBaseAddress = MCAL_CSL_MSS_CTRL_U_BASE;
            fssConf.extFlashSize  = Fls_Config_SFDP_Ptr->flashSize;
            Mcu_controlModuleUnlockMMR();
            FSS_selectRegionA((FSS_Handle)&fssConf);
            Mcu_controlModuleLockMMR();
            bootret = FSS_getBootRegion((FSS_Handle)&fssConf);
            AppUtils_printf("Bootret : %d\r\n", bootret);
            status = SystemP_SUCCESS;
        }
    }
#endif

    {
        HsmClient_config();
        /* loop through and request random number from HSM */
        /* also calculate the time spent doing the generation */
        int32_t     ret;
        uint32_t    length = 32;
        uint32_t    val[length / 4];
        HsmClient_t client;
        RNGReq_t    getRNG;

        uint32_t RngDrbgSeed[12] = {0x949db311, 0x1b53c4bf, 0x1d6cb9de, 0x75c85f23, 0xfe6bfe37, 0xae1c6462,
                                    0x9e45f958, 0x62493581, 0x8b5df32b, 0x7bc94d49, 0xa8e69e31, 0x9237ca9f};
        getRNG.DRBGMode          = 0x5A;
        getRNG.seedSizeInDWords  = SEED_SIZE_IN_DWORDS;
        getRNG.seedValue         = (uint32_t *)&RngDrbgSeed;
        getRNG.resultLength      = length;
        getRNG.resultPtr         = (uint8_t *)val;

        ret = HsmClient_register(&client, APP_CLIENT_ID);

        ret = HsmClient_getRandomNum(&client, &getRNG);

        /* print the random numbers generated */
        for (int i = 0; i < length / 4; i++)
        {
            AppUtils_printf("RNG output word -- 0x%X, %d\r\n", val[i], ret);
        }
    }

    {
        crypto_aes_cbc_128_main();
        crypto_hmac_sha512_main();
    }

    if (bootHandle != NULL_PTR)
    {
        status = Bootloader_parseAndLoadMultiCoreELF(bootHandle, &bootImageInfo);
        if (status == SystemP_SUCCESS)
        {
            AppUtils_printf(APP_NAME ": Parsing OK!!\n\r");
        }
        else
        {
            AppUtils_printf(APP_NAME ": Parsing Failed!!\n\r");
            status = SystemP_SUCCESS;
        }

        /* Run CPUs */
        if (status == SystemP_SUCCESS && (TRUE == Bootloader_isCorePresent(bootHandle, MCAL_CSL_CORE_ID_R5FSS1_1)))
        {
            status = Bootloader_runCpu(bootHandle, &bootImageInfo.cpuInfo[MCAL_CSL_CORE_ID_R5FSS1_1]);
        }
        if (status == SystemP_SUCCESS && (TRUE == Bootloader_isCorePresent(bootHandle, MCAL_CSL_CORE_ID_R5FSS1_0)))
        {
            status = Bootloader_runCpu(bootHandle, &bootImageInfo.cpuInfo[MCAL_CSL_CORE_ID_R5FSS1_0]);
        }
        if (status == SystemP_SUCCESS && (TRUE == Bootloader_isCorePresent(bootHandle, MCAL_CSL_CORE_ID_R5FSS0_1)))
        {
            status = Bootloader_runCpu(bootHandle, &bootImageInfo.cpuInfo[MCAL_CSL_CORE_ID_R5FSS0_1]);
        }
        if (status == SystemP_SUCCESS)
        {
            AppUtils_printf(APP_NAME "Image loading done, switching to application ...\r\n");
            status = Bootloader_runSelfCpu(bootHandle, &bootImageInfo);
        }
        /* it should not return here, if it does, then there was some error */
        Bootloader_close(bootHandle);
    }

    AppUtils_TimerDeinit();
    return (0);
}

void SchM_Enter_Fls_FLS_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Fls_FLS_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    Fls_TestPassed = E_NOT_OK;
    GT_assert(McalAppTrace, FALSE);
    return (E_OK);
}
Std_ReturnType Det_ReportRuntimeError(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId,
                                      VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) ErrorId)
{
    Fls_TestPassed = E_NOT_OK;
    GT_assert(McalAppTrace, FALSE);
    return (E_OK);
}
Std_ReturnType Det_ReportTransientFault(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId,
                                        VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) FaultId)
{
    Fls_TestPassed = E_NOT_OK;
    GT_assert(McalAppTrace, FALSE);
    return (E_OK);
}

#if (STD_ON == FLS_DMA_ENABLE)
void SchM_Enter_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif
