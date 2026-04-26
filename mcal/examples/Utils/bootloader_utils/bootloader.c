/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2021-2024 Texas Instruments Incorporated
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
 *  \file bootloader.c
 *
 *  \brief Bootloader Driver API source file.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "bootloader.h"
#include "bootloader_soc.h"
#include "bootloader_priv.h"
#include <string.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define GET_CACHE_ALIGNED_SIZE(x) \
    (((x) + (uint32_t)CacheP_CACHELINE_ALIGNMENT) & ~((uint32_t)CacheP_CACHELINE_ALIGNMENT - 1U))

/**
 * @brief Increase variable by a value while keeping alignment
 *
 * @param pValue Pointer to the value to increment
 * @param increment Amount to add to the value
 * @param alignment Alignment boundary in bytes
 */
static inline void Bootloader_alignedIncrement(uint32_t *pValue, uint32_t increment, uint32_t alignment)
{
    uint32_t newValue = *pValue + increment;
    *pValue           = newValue;
    if (0U != (newValue % alignment))
    {
        uint32_t remainder = newValue % alignment;
        *pValue            = newValue + (alignment - remainder);
    }
}

/*RPRC image ID for linux load only images */
#define RPRC_LINUX_LOAD_ONLY_IMAGE_ID (21U)
#define SEGMENT_MAP_NOTE_TYPE         (0xBBBB7777U)

/** Maximum allowed length of application certificate. */
#define MAX_APP_CERT_LENGTH (0x1000U)

/** This application segment can be encrypted. */
#define BOOTLOADER_APP_SEGMENT_CANBE_ENCRYPTED (0xA5U)
/** This application segment can never be encrypted. */
#define BOOTLOADER_APP_SEGMENT_CANNOTBE_ENCRYPTED (0x5AU)

/** The maximum possible size of RS note segment placed at the end of MCELF appimage. */
#define BOOTLOADER_MAX_RS_NOTE_SEGMENT_SIZE (48)

#define NOTE_SEGMENT_NOTE_TYPE_OTFA_CONFIG (0xDDDDBBBBU)

#define CONFIG_BOOTLOADER_NUM_INSTANCES (1U)
/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

extern Bootloader_Config gBootloaderConfig[CONFIG_BOOTLOADER_NUM_INSTANCES];
extern uint32_t          gBootloaderConfigNum;

#ifdef BOOTLOADER_SCRATCH_MEM_SUPPORT
extern Bootloader_MemArgs gMemBootloaderArgs;
#endif

uint8_t gElfHBuffer[GET_CACHE_ALIGNED_SIZE(ELF_HEADER_MAX_SIZE)]
    __attribute__((aligned((uint32_t)CacheP_CACHELINE_ALIGNMENT)));
uint8_t gNoteSegBuffer[GET_CACHE_ALIGNED_SIZE(ELF_NOTE_SEGMENT_MAX_SIZE)]
    __attribute__((aligned((uint32_t)CacheP_CACHELINE_ALIGNMENT)));
uint8_t gPHTBuffer[GET_CACHE_ALIGNED_SIZE((ELF_MAX_SEGMENTS * ELF_P_HEADER_MAX_SIZE))]
    __attribute__((aligned((uint32_t)CacheP_CACHELINE_ALIGNMENT)));
uint8_t vec_addrs[GET_CACHE_ALIGNED_SIZE(BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB)]
    __attribute__((aligned((uint32_t)CacheP_CACHELINE_ALIGNMENT)));
volatile uint32_t vec_size = 0U;

/** Buffer to store the Application X509 cert if present. */
uint8_t gX509Cert[MAX_APP_CERT_LENGTH];

volatile uint8_t *vector_table_loc = 0U;

/* ========================================================================== */
/*                             Function Definitions                           */
/* ========================================================================== */

Bootloader_Handle Bootloader_open(uint32_t instanceNum, Bootloader_Params *openParams)
{
    Bootloader_Config *config = NULL_PTR;

    if (instanceNum < gBootloaderConfigNum)
    {
        config = &gBootloaderConfig[instanceNum];
        if (config->fxns && config->fxns->imgOpenFxn && config->args)
        {
            int32_t status;

            status = config->fxns->imgOpenFxn(config->args, openParams);
            if (status != SystemP_SUCCESS)
            {
                config = NULL_PTR;
            }
        }
    }

    return (Bootloader_Handle)config;
}

void Bootloader_close(Bootloader_Handle handle)
{
    Bootloader_Config *config = (Bootloader_Config *)handle;

    if (config && config->fxns && config->fxns->imgCloseFxn)
    {
        config->fxns->imgCloseFxn(handle, config->args);
    }
}

int32_t Bootloader_initCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;

    status = Bootloader_socCpuRequest(cpuInfo->cpuId);

    status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

    if (SystemP_SUCCESS == status)
    {
        Bootloader_Config *config = (Bootloader_Config *)handle;
        status                    = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId, config->socCoreOpMode);
    }

    return status;
}

int32_t Bootloader_loadCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;

    status = Bootloader_socCpuRequest(cpuInfo->cpuId);

    status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

    if (SystemP_SUCCESS == status)
    {
        Bootloader_Config *config = (Bootloader_Config *)handle;
        status                    = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId, config->socCoreOpMode);
    }

    if (SystemP_SUCCESS == status)
    {
        if (cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
        {
            status = Bootloader_rprcImageLoad(handle, cpuInfo);
        }
    }

    return status;
}

int32_t Bootloader_runCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t   status     = SystemP_SUCCESS;
    uintptr_t entryPoint = cpuInfo->entryPoint;

    if (cpuInfo->rprcOffset == BOOTLOADER_INVALID_ID)
    {
        /* boot a dummy while(1) loop */
        entryPoint = 0;
    }
    status = Bootloader_socCpuResetRelease(cpuInfo->cpuId, entryPoint);

    if (SystemP_SUCCESS == status)
    {
        status = Bootloader_socCpuRelease(cpuInfo->cpuId);
    }

    if (status == SystemP_SUCCESS)
    {
        uint64_t cpuHz;

        cpuHz = Bootloader_socCpuGetClock(cpuInfo->cpuId);
        if (cpuHz > 0ULL)
        {
            AppUtils_printf(APP_NAME ":CPU %s is initialized to %d Hz !!!\r\n",
                            Bootloader_socGetCoreName(cpuInfo->cpuId), (uint32_t)cpuHz);
        }
    }

    return status;
}

int32_t Bootloader_runSelfCpu(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;

    AppUtils_printf(APP_NAME ":All done, reseting self ...\r\n\n");
    status = Bootloader_socCpuResetReleaseSelf();
    /* control will not reach here */

    return status;
}

int32_t Bootloader_bootCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;

    status = Bootloader_loadCpu(handle, cpuInfo);

    if (status == SystemP_SUCCESS)
    {
        status = Bootloader_runCpu(handle, cpuInfo);
    }

    return status;
}

int32_t Bootloader_bootSelfCpu(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t   status      = SystemP_SUCCESS;
    uint32_t  i           = 0;
    uint32_t *selfCpuList = Bootloader_socGetSelfCpuList();

    while (selfCpuList[i] != BOOTLOADER_INVALID_ID)
    {
        status = Bootloader_loadSelfCpu(handle, &bootImageInfo->cpuInfo[selfCpuList[i]], FALSE);
        if (status != SystemP_SUCCESS)
        {
            break;
        }
        i++;
    }

    if (status == SystemP_SUCCESS)
    {
        status = Bootloader_runSelfCpu(handle, bootImageInfo);
    }

    return status;
}

uint32_t Bootloader_getX509CertLen(uint8_t *x509_cert_ptr)
{
    uint32_t certLen  = 0;
    uint8_t *pCertLen = (uint8_t *)&certLen;

    if (*x509_cert_ptr == 0x30U)
    {
        certLen = *(x509_cert_ptr + 1U);

        /* If you need more than 2 bytes to store the cert length  */
        /* it means that the cert length is greater than 64 Kbytes */
        /* and we do not support it                                */
        if ((certLen <= 0x80U) || (certLen == 0x82U))
        {
            if (certLen == 0x82U)
            {
                *pCertLen        = *(x509_cert_ptr + 3U);
                *(pCertLen + 1U) = *(x509_cert_ptr + 2U);

                /* add current offset from start of x509 cert */
                certLen += 3U;
            }
            else
            {
                /* add current offset from start of x509 cert  */
                /* if cert len was obtained from 2nd byte i.e. */
                /* cert size is 127 bytes or less              */
                certLen += 1U;
            }

            /* certLen now contains the offset of the last byte */
            /* of the cert from the ccert_start. To get the size */
            /* of certificate, add 1                             */
            certLen += 1U;
        }
        else
        {
            certLen = 0U;
        }
    }

    return certLen;
}

uint8_t *Bootloader_findSeq(uint8_t *x509_cert_ptr, uint32_t x509_cert_size, uint8_t *seq_oid, uint8_t seq_len)
{
    uint8_t *x509_cert_end = x509_cert_ptr + x509_cert_size - (uint32_t)seq_len;
    uint8_t *certPtr       = x509_cert_ptr;
    uint8_t *result        = NULL_PTR;

    /* searching for the following byte seq in the cert */
    /* seq_id(0x30) seq_len(< 0x80) 0x06 0x09 0x2B...   */
    while ((certPtr < x509_cert_end) && (NULL_PTR == result))
    {
        if ((*certPtr == seq_oid[0]) && (*(certPtr + 2U) == seq_oid[2U]) && (*(certPtr - 2U) == 0x30U))
        {
            /* MISRA-C:2012 Rule 21.16 - Use byte-by-byte comparison for non-string data */
            uint8_t match = 1U;
            for (uint8_t idx = 0U; idx < seq_len; idx++)
            {
                if (certPtr[idx] != seq_oid[idx])
                {
                    match = 0U;
                    break;
                }
            }
            if (match == 1U)
            {
                /* found start boot_seq */
                result = (certPtr - 2U);
            }
        }
        certPtr++;
    }

    return result;
}

uint32_t Bootloader_getMsgLen(uint8_t *x509_cert_ptr, uint32_t x509_cert_size)
{
    uint8_t *boot_seq_ptr;
    uint32_t msg_len     = 0, boot_seq_len;
    uint8_t *msg_len_ptr = (uint8_t *)&msg_len;
    uint8_t  boot_seq_oid[11];
    Bootloader_socGetBootSeqOid(boot_seq_oid);
    boot_seq_ptr = Bootloader_findSeq(x509_cert_ptr, x509_cert_size, boot_seq_oid, sizeof(boot_seq_oid));

    /* length of seq is stored in the byte after the 0x30 seq_id */
    /* length of seq is stored as offset of the last byte of seq */
    /* from current offset. Jump to the end of the boot seq as   */
    /* the length of the message  is the last field of this seq  */
    boot_seq_ptr++;
    boot_seq_len = *boot_seq_ptr;
    boot_seq_ptr = boot_seq_ptr + boot_seq_len;

    /* The last integer in this sequence is the msg length    */
    /* integers are tagged 0x20, so search backwards for 0x20 */
    /* The msg size can be encoded in 1, 2, 3 or 4 bytes      */
    /* 0x02 0x01 0x##                                         */
    /* 0x02 0x02 0x## 0x##                                    */
    /* 0x02 0x03 0x## 0x## 0x##                               */
    /* 0x02 0x04 0x## 0x## 0x## 0x##                          */
    if ((*(boot_seq_ptr - 5U) == 0x02U) && (*(boot_seq_ptr - 4U) == 0x04U))
    {
        /* msg length encoded in 4 bytes */
        *msg_len_ptr        = *boot_seq_ptr;
        *(msg_len_ptr + 1U) = *(boot_seq_ptr - 1U);
        *(msg_len_ptr + 2U) = *(boot_seq_ptr - 2U);
        *(msg_len_ptr + 3U) = *(boot_seq_ptr - 3U);
    }
    else if ((*(boot_seq_ptr - 4U) == 0x02U) && (*(boot_seq_ptr - 3U) == 0x03U))
    {
        /* msg length encoded in 3 bytes */
        *msg_len_ptr        = *boot_seq_ptr;
        *(msg_len_ptr + 1U) = *(boot_seq_ptr - 1U);
        *(msg_len_ptr + 2U) = *(boot_seq_ptr - 2U);
    }
    else if ((*(boot_seq_ptr - 3U) == 0x02U) && (*(boot_seq_ptr - 2U) == 0x02U))
    {
        /* msg length encoded in 2 bytes */
        *msg_len_ptr        = *boot_seq_ptr;
        *(msg_len_ptr + 1U) = *(boot_seq_ptr - 1U);
    }
    else if ((*(boot_seq_ptr - 2U) == 0x02U) && (*(boot_seq_ptr - 1U) == 0x01U))
    {
        /* msg length encoded in 1 byte */
        *msg_len_ptr = *boot_seq_ptr;
    }
    else
    {
        /* MISRA compliance - default case */
    }

    return msg_len;
}

/* This API should only be called after all the rprc loading is complete */
uint32_t Bootloader_getMulticoreImageSize(Bootloader_Handle handle)
{
    uint32_t size = 0;

    if (handle != NULL_PTR)
    {
        Bootloader_Config *config = (Bootloader_Config *)handle;
        size                      = config->bootImageSize;
    }
    return size;
}

/* This API should only be called after the bootimage is parsed */
uint32_t Bootloader_isCorePresent(Bootloader_Handle handle, uint32_t cslCoreId)
{
    uint32_t retVal = FALSE;

    if (handle != NULL_PTR)
    {
        Bootloader_Config *config = (Bootloader_Config *)handle;
        if ((config->coresPresentMap & (1U << (uint32_t)cslCoreId)) != 0U)
        {
            retVal = TRUE;
        }
    }

    return retVal;
}

int32_t Bootloader_parseNoteSegment(Bootloader_Handle handle, uint32_t noteSegmentSz, uint32_t *segmentMapIdx)
{
    int32_t             status    = SystemP_SUCCESS;
    uint32_t            idx       = 0;
    Bootloader_ELFNote *notePtr   = (Bootloader_ELFNote *)gNoteSegBuffer;
    uint32_t            sgMpIdx   = 0;
    uint32_t            alignSize = 4U;

    while (idx < noteSegmentSz)
    {
        /* Read the type */
        idx += (ELF_NOTE_NAMESZ_SIZE + ELF_NOTE_DESCSZ_SIZE + ELF_NOTE_TYPE_SIZE);
        if (notePtr->type == SEGMENT_MAP_NOTE_TYPE)
        {
            sgMpIdx = idx + notePtr->namesz;
            if ((notePtr->namesz % alignSize) != 0U)
            {
                sgMpIdx += (alignSize - (notePtr->namesz % alignSize));
            }
            break;
        }
        else
        {
            idx += (notePtr->namesz + notePtr->descsz);
            if ((notePtr->namesz % alignSize) != 0U)
            {
                idx += (alignSize - (notePtr->namesz % alignSize));
            }
            if ((notePtr->descsz % alignSize) != 0U)
            {
                idx += (alignSize - (notePtr->descsz % alignSize));
            }
            notePtr = (Bootloader_ELFNote *)((uintptr_t)gNoteSegBuffer + idx);
        }
    }

    if (sgMpIdx == 0U)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        *segmentMapIdx = sgMpIdx;
    }

    return status;
}

int32_t Bootloader_getOTFAConfigFromNoteSegment(Bootloader_Handle handle, uint32_t noteSegmentSz,
                                                Bootloader_OtfaConfig *otfaConfig)
{
    int32_t status = SystemP_FAILURE;

    if ((NULL_PTR != handle) && (NULL_PTR != otfaConfig))
    {
        /* will walk through the entire note section */
        uint8_t  gotConfig = FALSE;
        uint32_t index     = 0;
        do
        {
            uint32_t       namesz = 0U;
            uint32_t       descsz = 0U;
            uint32_t       type   = 0U;
            /* MISRA-C:2012 AMD1 Rule 21.16 - Extract uint32_t from byte buffer */
            uint8_t const *pBuf = &gNoteSegBuffer[index];
            namesz              = ((uint32_t)pBuf[0]) | ((uint32_t)pBuf[1] << 8U) | ((uint32_t)pBuf[2] << 16U) |
                     ((uint32_t)pBuf[3] << 24U);
            Bootloader_alignedIncrement(&index, 4U, 4U);
            pBuf   = &gNoteSegBuffer[index];
            descsz = ((uint32_t)pBuf[0]) | ((uint32_t)pBuf[1] << 8U) | ((uint32_t)pBuf[2] << 16U) |
                     ((uint32_t)pBuf[3] << 24U);
            Bootloader_alignedIncrement(&index, 4U, 4U);
            pBuf = &gNoteSegBuffer[index];
            type = ((uint32_t)pBuf[0]) | ((uint32_t)pBuf[1] << 8U) | ((uint32_t)pBuf[2] << 16U) |
                   ((uint32_t)pBuf[3] << 24U);
            Bootloader_alignedIncrement(&index, 4U, 4U);
            uint8_t *name = &(gNoteSegBuffer[index]);
            Bootloader_alignedIncrement(&index, namesz, 4U);
            uint8_t *desc = &(gNoteSegBuffer[index]);
            Bootloader_alignedIncrement(&index, descsz, 4U);

            if ((NOTE_SEGMENT_NOTE_TYPE_OTFA_CONFIG == type) && (strcmp((const char *)name, "otfaConfig") == 0))
            {
                /*this note type is for otfa configuration*/
                memcpy((void *)otfaConfig, (void *)desc, sizeof(Bootloader_OtfaConfig));
                status    = SystemP_SUCCESS;
                gotConfig = TRUE;
            }
        } while ((index < noteSegmentSz) && (gotConfig == FALSE));
    }

    return status;
}

static int32_t Bootloader_verifySegmentAddr(uint32_t addr)
{
    int32_t status = SystemP_SUCCESS;

    /* Add check for SBL reserved memory */
    Bootloader_resMemSections *resMem;
    uint32_t                   resSectionCnt, start, end;

    resMem = Bootloader_socGetSBLMem();

    for (resSectionCnt = 0; resSectionCnt < resMem->numSections; resSectionCnt++)
    {
        start = resMem->memSection[resSectionCnt].memStart;
        end   = resMem->memSection[resSectionCnt].memEnd;
        if ((addr > start) && (addr < end))
        {
            status = SystemP_FAILURE;
            AppUtils_printf(
                APP_NAME ":Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", addr);
            break;
        }
    }

    return status;
}

int32_t Bootloader_parseAndLoadMultiCoreELF(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t  status          = SystemP_SUCCESS;
    uint32_t elfClass        = ELFCLASS_32;
    uint32_t elfSize         = ELF_HEADER_32_SIZE;
    uint32_t segmentMapIdx   = 0U;
    uint64_t bootImageLen    = 0U;
    uint32_t imgOffset       = 0U;
    uint64_t parsedImageSize = 0U;

    uint32_t rdSz = ELFCLASS_IDX + 1U;

    // uint8_t randomStringBuffer[BOOTLOADER_MAX_RS_NOTE_SEGMENT_SIZE];
    uint8_t  vec_present = 0U;
    uint32_t doAuth      = FALSE;

    uint32_t phoff       = 0U;
    uint32_t phtSize     = 0U;
    uint32_t numSegments = 0U;

    Bootloader_ELFH32 *elfPtr32 = NULL_PTR;
    Bootloader_ELFH64 *elfPtr64 = NULL_PTR;

    Bootloader_ELFPH32 *elfPhdrPtr32 = NULL_PTR;
    Bootloader_ELFPH64 *elfPhdrPtr64 = NULL_PTR;

    uint32_t noteSegmentSz     = 0U;
    uint32_t noteSegmentOffset = 0U;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    uint8_t initCpuDone[MCAL_CSL_CORE_ID_MAX] = {0};
    uint8_t ELFSTR[]                          = {0x7FU, (uint8_t)'E', (uint8_t)'L', (uint8_t)'F'};

    if ((config->fxns->imgReadFxn == NULL) || (config->fxns->imgSeekFxn == NULL_PTR))
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        config->fxns->imgSeekFxn(0, config->args);

        doAuth = ((Bootloader_socIsAuthRequired() == TRUE) && (config->isAppimageSigned == TRUE));
    }

    /*
        If authentication is required, copy and parse the certificate for length and application image length.
        Send the certificate for verification to the HSM by starting the Streaming authentication.
    */
    // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
    // {
    //     uint8_t x509Header[4U];
    //     config->fxns->imgReadFxn(x509Header, 4U, config->args);
    //     imgOffset = Bootloader_getX509CertLen(x509Header);

    //     /* Certificate length is not greater than the maximum allowed value. */
    //     if (imgOffset > MAX_APP_CERT_LENGTH)
    //     {
    //         status = SystemP_FAILURE;
    //     }
    //     else
    //     {
    //         memcpy(&gX509Cert[0], x509Header, 4U);
    //         config->fxns->imgReadFxn(&gX509Cert[4], imgOffset, config->args);
    //         bootImageLen = Bootloader_getMsgLen(gX509Cert, imgOffset);

    //         status = Bootloader_authStart((uintptr_t)gX509Cert, imgOffset);
    //     }
    // }

    if (status == SystemP_SUCCESS)
    {
        /* Parse the ELF magic bytes and match with the intended value. */
        config->fxns->imgSeekFxn(imgOffset, config->args);
        status = config->fxns->imgReadFxn(gElfHBuffer, rdSz, config->args);

        /* MISRA-C:2012 AMD1 Rule 21.16 - Compare byte arrays without memcmp */
        if ((gElfHBuffer[0] != ELFSTR[0]) || (gElfHBuffer[1] != ELFSTR[1]) || (gElfHBuffer[2] != ELFSTR[2]) ||
            (gElfHBuffer[3] != ELFSTR[3]))
        {
            status = SystemP_FAILURE;
        }

        elfClass = gElfHBuffer[ELFCLASS_IDX];

        if (elfClass == ELFCLASS_64)
        {
            elfSize = ELF_HEADER_64_SIZE;
        }
    }

    if (status == SystemP_SUCCESS)
    {
        /* If ELF magic bytes match, then read the whole ELF buffer. */
        config->fxns->imgSeekFxn((imgOffset + rdSz), config->args);
        status           = config->fxns->imgReadFxn((gElfHBuffer + rdSz), (elfSize - rdSz), config->args);
        parsedImageSize += elfSize;
    }

    // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
    // {
    //     /* Send the ELF header for streaming authentication to the HSM. */
    //     status = Bootloader_authUpdate((uintptr_t)gElfHBuffer, elfSize, BOOTLOADER_APP_SEGMENT_CANNOTBE_ENCRYPTED);
    // }

    if (status == SystemP_SUCCESS)
    {
        elfPtr32 = (Bootloader_ELFH32 *)gElfHBuffer;
        elfPtr64 = (Bootloader_ELFH64 *)gElfHBuffer;

        /* Calculate the Program Header Table size. */
        phtSize = ((uint32_t)elfPtr32->e_phnum * (uint32_t)elfPtr32->e_phentsize);

        if (elfClass == ELFCLASS_64)
        {
            phtSize = ((uint32_t)elfPtr64->e_phnum * (uint32_t)elfPtr64->e_phentsize);
        }

        numSegments = elfPtr32->e_phnum;

        if (elfClass == ELFCLASS_64)
        {
            numSegments = elfPtr64->e_phnum;
        }

        /* Check if number of PHT entries are <= MAX */
        if (numSegments > ELF_MAX_SEGMENTS)
        {
            status = SystemP_FAILURE;
        }
    }

    if (status == SystemP_SUCCESS)
    {
        /* From the PHT offset, read the PHT and place it in the buffer. */
        phoff = elfPtr32->e_phoff;

        if (elfClass == ELFCLASS_64)
        {
            phoff = elfPtr64->e_phoff;
        }

        config->fxns->imgSeekFxn(imgOffset + phoff, config->args);
        status           = config->fxns->imgReadFxn((void *)(gPHTBuffer), phtSize, config->args);
        parsedImageSize += phtSize;
    }

    // if(status == SystemP_SUCCESS && (doAuth == TRUE))
    // {
    //     /* Send the PHT for streaming authentication to the HSM. */
    //     status = Bootloader_authUpdate((uintptr_t)(gPHTBuffer), phtSize, BOOTLOADER_APP_SEGMENT_CANNOTBE_ENCRYPTED);
    // }

    if (status == SystemP_SUCCESS)
    {
        elfPhdrPtr32 = (Bootloader_ELFPH32 *)gPHTBuffer;
        elfPhdrPtr64 = (Bootloader_ELFPH64 *)gPHTBuffer;

        /* Note segment is always the first segment at index 0. */
        noteSegmentSz     = elfPhdrPtr32[0].filesz;
        noteSegmentOffset = elfPhdrPtr32[0].offset;

        if (elfClass == ELFCLASS_64)
        {
            noteSegmentSz     = elfPhdrPtr64[0].filesz;
            noteSegmentOffset = elfPhdrPtr64[0].offset;
        }
    }

    if (status == SystemP_SUCCESS)
    {
        /* Read the note segment buffer from the note segment flash offset. */
        config->fxns->imgSeekFxn(imgOffset + noteSegmentOffset, config->args);
        status           = config->fxns->imgReadFxn((void *)(gNoteSegBuffer), noteSegmentSz, config->args);
        parsedImageSize += noteSegmentSz;
    }

    if (status == SystemP_SUCCESS)
    {
        /* Parse the note segment buffer. */
        status = Bootloader_parseNoteSegment(handle, noteSegmentSz, &segmentMapIdx);
    }

    // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
    // {
    //     /* Send the note segment for streaming authentication to the HSM. */
    //     status = Bootloader_authUpdate((uintptr_t)gNoteSegBuffer, noteSegmentSz,
    //     BOOTLOADER_APP_SEGMENT_CANNOTBE_ENCRYPTED);
    // }

    if ((status == SystemP_SUCCESS) && (elfClass == ELFCLASS_32))
    {
        /*
            Note segment is the first segment in MCELF. The loadable are expected to be present after that.
            So we set the index i to be 1 in the following loop.
        */
        for (int32_t i = 1; (i < (int32_t)elfPtr32->e_phnum); i++)
        {
            if ((elfPhdrPtr32[i].filesz != 0U) &&
                ((((doAuth == TRUE) && (elfPhdrPtr32[i].filesz <= (bootImageLen - parsedImageSize)))) ||
                 (doAuth == FALSE)))
            {
                if (elfPhdrPtr32[i].type == PT_LOAD)
                {
                    uint8_t cpuId = gNoteSegBuffer[segmentMapIdx + (uint32_t)((uint32_t)i - 1U)];

                    if (initCpuDone[cpuId] == 0U)
                    {
                        status                   = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cpuId]);
                        config->coresPresentMap |= (1U << (uint32_t)cpuId);
                        initCpuDone[cpuId]       = 1U;
                    }
                    if (status == SystemP_SUCCESS)
                    {
                        config->fxns->imgSeekFxn(imgOffset + elfPhdrPtr32[i].offset, config->args);
                        uint32_t addr = Bootloader_socTranslateSectionAddr(
                            gNoteSegBuffer[segmentMapIdx + ((uint32_t)i - 1U)], elfPhdrPtr32[i].vaddr);
                        /*
                            Do not overwrite the vector table present at address 0 till the authentication is complete.
                            Just copy this into a buffer and send the buffer address for authentication.
                        */
                        if (addr == 0U)
                        {
                            void *tcm_mirror_addr = (void *)&vec_addrs[0U];
                            vec_present           = 1U;
                            vec_size              = elfPhdrPtr32[i].filesz;

                            if (vec_size > BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB)
                            {
                                /* If the address of the segment is valid, load the segment from the flash. */
                                status = config->fxns->imgReadFxn(tcm_mirror_addr, BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB,
                                                                  config->args);
                                config->bootImageSize += BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB;
                                parsedImageSize       += BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB;

                                // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
                                // {
                                //     /* Send the loadable segment info for Streaming Authentication to the HSM. */
                                //     status = Bootloader_authUpdate((uintptr_t)tcm_mirror_addr,
                                //     BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB, BOOTLOADER_APP_SEGMENT_CANBE_ENCRYPTED);
                                // }

                                /* If the address of the segment is valid, load the segment from the flash. */
                                uint32_t segmentAddr = addr + BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB;
                                status = config->fxns->imgReadFxn((void *)(uint32_t *)(uintptr_t)segmentAddr,
                                                                  (vec_size - BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB),
                                                                  config->args);
                                config->bootImageSize += (vec_size - BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB);
                                parsedImageSize       += (vec_size - BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB);

                                // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
                                // {
                                //     /* Send the loadable segment info for Streaming Authentication to the HSM. */
                                //     status = Bootloader_authUpdate((uintptr_t)(addr +
                                //     BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB), (vec_size -
                                //     BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB), BOOTLOADER_APP_SEGMENT_CANBE_ENCRYPTED);
                                // }

                                /* To revert the pending copy size */
                                vec_size = BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB;
                            }
                            else
                            {
                                if (status == SystemP_SUCCESS)
                                {
                                    /* If the address of the segment is valid, load the segment from the flash. */
                                    status =
                                        config->fxns->imgReadFxn(tcm_mirror_addr, elfPhdrPtr32[i].filesz, config->args);
                                    config->bootImageSize += elfPhdrPtr32[i].filesz;
                                    parsedImageSize       += elfPhdrPtr32[i].filesz;
                                }

                                // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
                                // {
                                //     /* Send the loadable segment info for Streaming Authentication to the HSM. */
                                //     status = Bootloader_authUpdate((uintptr_t)tcm_mirror_addr,
                                //     elfPhdrPtr32[i].filesz, BOOTLOADER_APP_SEGMENT_CANBE_ENCRYPTED);
                                // }
                            }
                        }
                        else
                        {
                            /* Verify the address of all segments except those which are local or global variables of
                             * the SBL. */
                            status = Bootloader_verifySegmentAddr(addr);

                            if (status == SystemP_SUCCESS)
                            {
                                /* If the address of the segment is valid, load the segment from the flash. */
                                status                 = config->fxns->imgReadFxn((void *)(uint32_t *)(uintptr_t)addr,
                                                                                  elfPhdrPtr32[i].filesz, config->args);
                                config->bootImageSize += elfPhdrPtr32[i].filesz;
                                parsedImageSize       += elfPhdrPtr32[i].filesz;
                            }

                            // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
                            // {
                            //     /* Send the loadable segment info for Streaming Authentication to the HSM. */
                            //     status = Bootloader_authUpdate((uintptr_t)addr, elfPhdrPtr32[i].filesz,
                            //     BOOTLOADER_APP_SEGMENT_CANBE_ENCRYPTED);
                            // }
                        }
                    }
                }
                else
                {
                    /* Ignore this segment */
                }
            }
            else if ((elfPhdrPtr32[i].filesz > (bootImageLen - parsedImageSize)) && (doAuth == TRUE))
            {
                /* If the segment size is greater than the remaining size left. */
                status = SystemP_FAILURE;
            }
            else
            {
                /* NO LOAD segment, do nothing */
            }

            /* Exit loop if status indicates failure */
            if (status != SystemP_SUCCESS)
            {
                break;
            }
        }
    }
    else if ((status == SystemP_SUCCESS) && (elfClass == ELFCLASS_64))
    {
        /*
            Note segment is the first segment in MCELF. The loadable are expected to be present after that.
            So we set the index i to be 1 in the following loop.
        */
        for (int32_t i = 1; (i < (int32_t)elfPtr64->e_phnum); i++)
        {
            if ((elfPhdrPtr64[i].filesz != 0U) &&
                (((doAuth == TRUE) && (elfPhdrPtr64[i].filesz <= (bootImageLen - parsedImageSize))) ||
                 (doAuth == FALSE)))
            {
                if (elfPhdrPtr64[i].type == PT_LOAD)
                {
                    config->fxns->imgSeekFxn(imgOffset + elfPhdrPtr64[i].offset, config->args);
                    uint32_t addr = Bootloader_socTranslateSectionAddr(
                        gNoteSegBuffer[segmentMapIdx + ((uint32_t)i - 1U)], elfPhdrPtr64[i].vaddr);
                    /*
                            Do not overwrite the vector table present at address 0 till the authentication is complete.
                            Just copy this into a buffer and send the buffer address for authentication.
                    */
                    if (addr == 0U)
                    {
                        addr        = (uint32_t)&vec_addrs[0U];
                        vec_present = 1U;
                        vec_size    = elfPhdrPtr64[i].filesz;

                        if (vec_size > BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB)
                        {
                            status = SystemP_FAILURE;
                        }
                    }
                    else
                    {
                        /* Verify the address of all segments except those which are local or global variables of the
                         * SBL. */
                        status = Bootloader_verifySegmentAddr(addr);
                    }

                    if (status == SystemP_SUCCESS)
                    {
                        status = config->fxns->imgReadFxn((void *)(uint32_t *)(uintptr_t)addr, elfPhdrPtr64[i].filesz,
                                                          config->args);
                        config->bootImageSize += elfPhdrPtr64[i].filesz;
                        parsedImageSize       += elfPhdrPtr64[i].filesz;
                    }

                    // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
                    // {
                    //     /* Send the loadable segment info for Streaming Authentication to the HSM. */
                    //     status = Bootloader_authUpdate((uintptr_t)addr, elfPhdrPtr64[i].filesz,
                    //     BOOTLOADER_APP_SEGMENT_CANBE_ENCRYPTED);
                    // }
                }
                else
                {
                    /* Ignore this segment */
                }
            }
            else if ((elfPhdrPtr64[i].filesz > (bootImageLen - parsedImageSize)) && (doAuth == TRUE))
            {
                /* If the segment size is greater than the remaining size left. */
                status = SystemP_FAILURE;
            }
            else
            {
                /* NO LOAD segment, do nothing */
            }

            /* Exit loop if status indicates failure */
            if (status != SystemP_SUCCESS)
            {
                break;
            }
        }
    }
    else
    {
        /* Only two ELF classes are supported EFLCLASS_32 or ELFCLASS_64 */
        status = SystemP_FAILURE;
    }

    // if((status == SystemP_SUCCESS) && (bootImageLen > parsedImageSize) && (doAuth == TRUE))
    // {
    //     if ((bootImageLen - parsedImageSize) > BOOTLOADER_MAX_RS_NOTE_SEGMENT_SIZE)
    //     {
    //         status = SystemP_FAILURE;
    //     }

    //     if (status == SystemP_SUCCESS)
    //     {
    //         /* This segement contains the random string required to verify decryption. */
    //         config->fxns->imgReadFxn((void *)randomStringBuffer, (bootImageLen - parsedImageSize), config->args);
    //         status = Bootloader_authUpdate((uintptr_t)randomStringBuffer, (bootImageLen - parsedImageSize),
    //         BOOTLOADER_APP_SEGMENT_CANBE_ENCRYPTED);
    //     }
    // }
    // else if ((status == SystemP_SUCCESS) && (doAuth == FALSE))
    // {
    //     status = SystemP_SUCCESS;
    // }
    // else
    // {
    //     /*
    //         In this case,
    //             1. Either the status is SystemP_FAILURE or,
    //             2. the random string is not present which is always there in MCELF.
    //             3. Or the parsedImage has exceeded the size of bootImageLen
    //     */
    //     status = SystemP_FAILURE;
    // }

    // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
    // {
    //     /* Request the HSM to close the Streaming authentication and do in place decryption if required. */
    //     status = Bootloader_authFinish();
    // }

    if ((status == SystemP_SUCCESS) && (vec_present == 1U))
    {
        /* Since authentication is complete now replace the vector table with the one from the application image if
         * required. */

        /* Bounds check to ensure vec_size does not exceed buffer capacity */
        if (vec_size <= BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB)
        {
            /*
                Invalidate the local cache so as to read the value of the vectors from the Shared memory.
                This is required in the case of decryption where the HSM core has decrypted the contents
                but the modified contents do not show up in the cache.
            */
            Mcal_CacheP_inv(vec_addrs, vec_size, Mcal_CacheP_TYPE_ALLD);

            /* MISRA-C:2012 AMD1 Rule 21.16 - Cast away volatile for memcpy */
            uint8_t *pDest = (uint8_t *)(uintptr_t)vector_table_loc;
            (void)memcpy((void *)pDest, (const void *)vec_addrs, vec_size);

            /*
                Write the contents of the vector address in shared memory so that these are used by the CPU after reset.
            */
            Mcal_CacheP_wbInv((void *)vector_table_loc, vec_size, Mcal_CacheP_TYPE_ALLD);
        }
        else
        {
            /* vec_size exceeds buffer capacity - this should not happen if code flow is correct */
            status = SystemP_FAILURE;
        }
    }

    return status;
}

void Bootloader_Params_init(Bootloader_Params *params)
{
    params->memArgsAppImageBaseAddr = BOOTLOADER_INVALID_ID;
}

void Bootloader_CpuInfo_init(Bootloader_CpuInfo *cpuInfo)
{
    cpuInfo->cpuId      = MCAL_CSL_CORE_ID_MAX;
    cpuInfo->clkHz      = 0U;
    cpuInfo->rprcOffset = BOOTLOADER_INVALID_ID;
    cpuInfo->entryPoint = BOOTLOADER_INVALID_ID;
}

void Bootloader_BootImageInfo_init(Bootloader_BootImageInfo *bootImageInfo)
{
    uint16_t i;

    for (i = 0; i < MCAL_CSL_CORE_ID_MAX; i++)
    {
        Bootloader_CpuInfo_init(&bootImageInfo->cpuInfo[i]);
        bootImageInfo->cpuInfo[i].cpuId = i;
        bootImageInfo->cpuInfo[i].clkHz = Bootloader_socCpuGetClkDefault(i);
    }
}
