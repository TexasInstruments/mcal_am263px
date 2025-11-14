/*
 *  Copyright (C) 2021-2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

#define GET_CACHE_ALIGNED_SIZE(x) ((x + CacheP_CACHELINE_ALIGNMENT) & ~(CacheP_CACHELINE_ALIGNMENT - 1))

/** Increase variable A by number B while keping the alignemnt of C bytes */
#define ALIGNED_INCREMENT(A, B, C)                          \
    do                                                      \
    {                                                       \
        A = (A = A + B, (A % C) > 0 ? A + C - (A % C) : A); \
    } while (0)

/*RPRC image ID for linux load only images */
#define RPRC_LINUX_LOAD_ONLY_IMAGE_ID (21U)
#define SEGMENT_MAP_NOTE_TYPE         (0xBBBB7777)

/** Maximum allowed length of application certificate. */
#define MAX_APP_CERT_LENGTH (0x1000U)

/** This application segment can be encrypted. */
#define BOOTLOADER_APP_SEGMENT_CANBE_ENCRYPTED (0xA5U)
/** This application segment can never be encrypted. */
#define BOOTLOADER_APP_SEGMENT_CANNOTBE_ENCRYPTED (0x5AU)

/** The maximum possible size of RS note segment placed at the end of MCELF appimage. */
#define BOOTLOADER_MAX_RS_NOTE_SEGMENT_SIZE (48)

#define NOTE_SEGMENT_NOTE_TYPE_OTFA_CONFIG (0xDDDDBBBB)

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

extern Bootloader_Config gBootloaderConfig[];
extern uint32_t          gBootloaderConfigNum;

#ifdef BOOTLOADER_SCRATCH_MEM_SUPPORT
extern Bootloader_MemArgs gMemBootloaderArgs;
#endif

uint8_t gElfHBuffer[GET_CACHE_ALIGNED_SIZE(ELF_HEADER_MAX_SIZE)] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
uint8_t gNoteSegBuffer[GET_CACHE_ALIGNED_SIZE(ELF_NOTE_SEGMENT_MAX_SIZE)]
    __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
uint8_t gPHTBuffer[GET_CACHE_ALIGNED_SIZE(ELF_MAX_SEGMENTS * ELF_P_HEADER_MAX_SIZE)]
    __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
uint8_t vec_addrs[GET_CACHE_ALIGNED_SIZE(BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB)]
    __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
volatile uint32_t vec_size = 0U;

/** Buffer to store the Application X509 cert if present. */
uint8_t gX509Cert[MAX_APP_CERT_LENGTH];

volatile uint8_t *vector_table_loc = 0U;

/* ========================================================================== */
/*                             Function Definitions                           */
/* ========================================================================== */

Bootloader_Handle Bootloader_open(uint32_t instanceNum, Bootloader_Params *openParams)
{
    Bootloader_Config *config = NULL;

    if (instanceNum < gBootloaderConfigNum)
    {
        config = &gBootloaderConfig[instanceNum];
        if (config->fxns && config->fxns->imgOpenFxn && config->args)
        {
            int32_t status;

            status = config->fxns->imgOpenFxn(config->args, openParams);
            if (status != SystemP_SUCCESS)
            {
                config = NULL;
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
        if (cpuHz > 0)
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

    if (*x509_cert_ptr != 0x30)
    {
        return 0;
    }

    certLen = *(x509_cert_ptr + 1);

    /* If you need more than 2 bytes to store the cert length  */
    /* it means that the cert length is greater than 64 Kbytes */
    /* and we do not support it                                */
    if ((certLen > 0x80) && (certLen != 0x82))
    {
        return 0;
    }

    if (certLen == 0x82)
    {
        *pCertLen       = *(x509_cert_ptr + 3);
        *(pCertLen + 1) = *(x509_cert_ptr + 2);

        /* add current offset from start of x509 cert */
        certLen += 3;
    }
    else
    {
        /* add current offset from start of x509 cert  */
        /* if cert len was obtained from 2nd byte i.e. */
        /* cert size is 127 bytes or less              */
        certLen += 1;
    }

    /* certLen now contains the offset of the last byte */
    /* of the cert from the ccert_start. To get the size */
    /* of certificate, add 1                             */

    return certLen + 1;
}

uint8_t *Bootloader_findSeq(uint8_t *x509_cert_ptr, uint32_t x509_cert_size, uint8_t *seq_oid, uint8_t seq_len)
{
    uint8_t *x509_cert_end = x509_cert_ptr + x509_cert_size - seq_len;

    /* searching for the following byte seq in the cert */
    /* seq_id(0x30) seq_len(< 0x80) 0x06 0x09 0x2B...   */
    while (x509_cert_ptr < x509_cert_end)
    {
        if ((*x509_cert_ptr == seq_oid[0]) && (*(x509_cert_ptr + 2) == seq_oid[2]) && (*(x509_cert_ptr - 2) == 0x30))
        {
            if ((memcmp((const void *)x509_cert_ptr, (const void *)seq_oid, seq_len)) == 0)
            {
                /* return start boot_seq */
                return (x509_cert_ptr - 2);
            }
        }
        x509_cert_ptr++;
    }

    return NULL;
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
    boot_seq_len = *(++boot_seq_ptr);
    boot_seq_ptr = boot_seq_ptr + boot_seq_len;

    /* The last integer in this sequence is the msg length    */
    /* integers are tagged 0x20, so search backwards for 0x20 */
    /* The msg size can be encoded in 1, 2, 3 or 4 bytes      */
    /* 0x02 0x01 0x##                                         */
    /* 0x02 0x02 0x## 0x##                                    */
    /* 0x02 0x03 0x## 0x## 0x##                               */
    /* 0x02 0x04 0x## 0x## 0x## 0x##                          */
    if ((*(boot_seq_ptr - 5) == 0x02) && (*(boot_seq_ptr - 4) == 0x04))
    {
        /* msg length encoded in 4 bytes */
        *msg_len_ptr       = *boot_seq_ptr;
        *(msg_len_ptr + 1) = *(boot_seq_ptr - 1);
        *(msg_len_ptr + 2) = *(boot_seq_ptr - 2);
        *(msg_len_ptr + 3) = *(boot_seq_ptr - 3);
    }
    else if ((*(boot_seq_ptr - 4) == 0x02) && (*(boot_seq_ptr - 3) == 0x03))
    {
        /* msg length encoded in 3 bytes */
        *msg_len_ptr       = *boot_seq_ptr;
        *(msg_len_ptr + 1) = *(boot_seq_ptr - 1);
        *(msg_len_ptr + 2) = *(boot_seq_ptr - 2);
    }
    else if ((*(boot_seq_ptr - 3) == 0x02) && (*(boot_seq_ptr - 2) == 0x02))
    {
        /* msg length encoded in 2 bytes */
        *msg_len_ptr       = *boot_seq_ptr;
        *(msg_len_ptr + 1) = *(boot_seq_ptr - 1);
    }
    else if ((*(boot_seq_ptr - 2) == 0x02) && (*(boot_seq_ptr - 1) == 0x01))
    {
        /* msg length encoded in 1 byte */
        *msg_len_ptr = *boot_seq_ptr;
    }

    return msg_len;
}

/* This API should only be called after all the rprc loading is complete */
uint32_t Bootloader_getMulticoreImageSize(Bootloader_Handle handle)
{
    uint32_t size = 0;

    if (handle != NULL)
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

    if (handle != NULL)
    {
        Bootloader_Config *config = (Bootloader_Config *)handle;
        if ((config->coresPresentMap & (1 << cslCoreId)) != 0)
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
            if (notePtr->namesz % alignSize != 0)
            {
                sgMpIdx += (alignSize - (notePtr->namesz % alignSize));
            }
            break;
        }
        else
        {
            idx += notePtr->namesz + notePtr->descsz;
            if (notePtr->namesz % alignSize != 0)
            {
                idx += (alignSize - (notePtr->namesz % alignSize));
            }
            if (notePtr->descsz % alignSize != 0)
            {
                idx += (alignSize - (notePtr->descsz % alignSize));
            }
            notePtr = (Bootloader_ELFNote *)((uintptr_t)gNoteSegBuffer + idx);
        }
    }

    if (sgMpIdx == 0)
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

    if (NULL != handle && NULL != otfaConfig)
    {
        /* will walk through the entire note section */
        uint8_t  gotConfig = FALSE;
        uint32_t index     = 0;
        do
        {
            uint32_t namesz = *(uint32_t *)(gNoteSegBuffer + index);
            ALIGNED_INCREMENT(index, 4, 4);
            uint32_t descsz = *(uint32_t *)(gNoteSegBuffer + index);
            ALIGNED_INCREMENT(index, 4, 4);
            uint32_t type = *(uint32_t *)(gNoteSegBuffer + index);
            ALIGNED_INCREMENT(index, 4, 4);
            uint8_t *name = &(gNoteSegBuffer[index]);
            ALIGNED_INCREMENT(index, namesz, 4);
            uint8_t *desc = &(gNoteSegBuffer[index]);
            ALIGNED_INCREMENT(index, descsz, 4);

            if (NOTE_SEGMENT_NOTE_TYPE_OTFA_CONFIG == type && strcmp((const char *)name, "otfaConfig") == 0)
            {
                /*this note type is for otfa configuration*/
                memcpy((void *)otfaConfig, (void *)desc, sizeof(Bootloader_OtfaConfig));
                status    = SystemP_SUCCESS;
                gotConfig = TRUE;
            }
        } while (index < noteSegmentSz && gotConfig == FALSE);
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

    Bootloader_ELFH32 *elfPtr32 = NULL;
    Bootloader_ELFH64 *elfPtr64 = NULL;

    Bootloader_ELFPH32 *elfPhdrPtr32 = NULL;
    Bootloader_ELFPH64 *elfPhdrPtr64 = NULL;

    uint32_t noteSegmentSz     = 0U;
    uint32_t noteSegmentOffset = 0U;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    uint8_t initCpuDone[MCAL_CSL_CORE_ID_MAX] = {0};
    char    ELFSTR[]                          = {0x7F, 'E', 'L', 'F'};

    if (config->fxns->imgReadFxn == NULL || config->fxns->imgSeekFxn == NULL)
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

        if (memcmp(ELFSTR, gElfHBuffer, 4) != 0)
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
        phtSize = ((elfPtr32->e_phnum) * (elfPtr32->e_phentsize));

        if (elfClass == ELFCLASS_64)
        {
            phtSize = ((elfPtr64->e_phnum) * (elfPtr64->e_phentsize));
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
        for (int32_t i = 1; ((i < elfPtr32->e_phnum) && (status == SystemP_SUCCESS)); i++)
        {
            if ((elfPhdrPtr32[i].filesz != 0) &&
                (((doAuth == TRUE) && (elfPhdrPtr32[i].filesz <= (bootImageLen - parsedImageSize))) ||
                 (doAuth == FALSE)))
            {
                if (elfPhdrPtr32[i].type == PT_LOAD)
                {
                    uint8_t cpuId = gNoteSegBuffer[segmentMapIdx + i - 1];

                    if (!initCpuDone[cpuId])
                    {
                        status                   = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cpuId]);
                        config->coresPresentMap |= 1 << cpuId;
                        initCpuDone[cpuId]       = 1;
                    }
                    if (status == SystemP_SUCCESS)
                    {
                        config->fxns->imgSeekFxn(imgOffset + elfPhdrPtr32[i].offset, config->args);
                        uint32_t addr = Bootloader_socTranslateSectionAddr(gNoteSegBuffer[segmentMapIdx + i - 1],
                                                                           elfPhdrPtr32[i].vaddr);
                        /*
                            Do not overwrite the vector table present at address 0 till the authentication is complete.
                            Just copy this into a buffer and send the buffer address for authentication.
                        */
                        if (addr == 0U)
                        {
                            uint32_t tcm_mirror_addr = (uint32_t)&vec_addrs[0U];
                            vec_present              = 1U;
                            vec_size                 = elfPhdrPtr32[i].filesz;

                            if (vec_size > BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB)
                            {
                                /* If the address of the segment is valid, load the segment from the flash. */
                                status                 = config->fxns->imgReadFxn((void *)tcm_mirror_addr,
                                                                                  BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB, config->args);
                                config->bootImageSize += BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB;
                                parsedImageSize       += BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB;

                                // if((status == SystemP_SUCCESS) && (doAuth == TRUE))
                                // {
                                //     /* Send the loadable segment info for Streaming Authentication to the HSM. */
                                //     status = Bootloader_authUpdate((uintptr_t)tcm_mirror_addr,
                                //     BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB, BOOTLOADER_APP_SEGMENT_CANBE_ENCRYPTED);
                                // }

                                /* If the address of the segment is valid, load the segment from the flash. */
                                status = config->fxns->imgReadFxn((void *)(addr + BOOTLOADER_MAX_SBL_SIZE_IN_TCM_KB),
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
                                    status = config->fxns->imgReadFxn((void *)tcm_mirror_addr, elfPhdrPtr32[i].filesz,
                                                                      config->args);
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
                                status = config->fxns->imgReadFxn((void *)addr, elfPhdrPtr32[i].filesz, config->args);
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
        }
    }
    else if ((status == SystemP_SUCCESS) && (elfClass == ELFCLASS_64))
    {
        /*
            Note segment is the first segment in MCELF. The loadable are expected to be present after that.
            So we set the index i to be 1 in the following loop.
        */
        for (int32_t i = 1; ((i < elfPtr64->e_phnum) && (status == SystemP_SUCCESS)); i++)
        {
            if ((elfPhdrPtr64[i].filesz != 0) &&
                (((doAuth == TRUE) && (elfPhdrPtr64[i].filesz <= (bootImageLen - parsedImageSize))) ||
                 (doAuth == FALSE)))
            {
                if (elfPhdrPtr64[i].type == PT_LOAD)
                {
                    config->fxns->imgSeekFxn(imgOffset + elfPhdrPtr64[i].offset, config->args);
                    uint32_t addr = Bootloader_socTranslateSectionAddr(gNoteSegBuffer[segmentMapIdx + i - 1],
                                                                       elfPhdrPtr64[i].vaddr);
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
                        status = config->fxns->imgReadFxn((void *)addr, elfPhdrPtr64[i].filesz, config->args);
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

        /*
            Invalidate the local cache so as to read the value of the vectors from the Shared memory.
            This is required in the case of decryption where the HSM core has decrypted the contents
            but the modified contents do not show up in the cache.
        */
        Mcal_CacheP_inv(vec_addrs, vec_size, Mcal_CacheP_TYPE_ALLD);

        (void)memcpy((void *)vector_table_loc, vec_addrs, vec_size);

        /*
            Write the contents of the vector address in shared memory so that these are used by the CPU after reset.
        */
        Mcal_CacheP_wbInv((void *)vector_table_loc, vec_size, Mcal_CacheP_TYPE_ALLD);
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
