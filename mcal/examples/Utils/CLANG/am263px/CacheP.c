/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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

#include "CacheP.h"
#include "app_utils.h"

#define CACHE_SECTION __attribute__((section(".text.cache")))

/* APIs defined in Mcal_CacheP_armv7r_asm.S */
uint32 Mcal_CacheP_getCacheLevelInfo(uint32 level);
uint32 Mcal_CacheP_getEnabled();
void   Mcal_CacheP_configForceWrThru(uint32 enable);
void   Mcal_CacheP_disableL1d();
void   Mcal_CacheP_disableL1p();
void   Mcal_CacheP_enableL1d();
void   Mcal_CacheP_enableL1p();
void   Mcal_CacheP_setDLFO();

uint32 mcal_gCacheL1dCacheLineSize = 32;
uint32 mcal_gCacheL1pCacheLineSize = 32;

Mcal_CacheP_Config mcal_gCacheConfig = {
    .enable            = 1,
    .enableForceWrThru = 1,
};

/* these are defined as part of SysConfig */
extern Mcal_CacheP_Config mcal_gCacheConfig;

void CACHE_SECTION Mcal_CacheP_init()
{
    uint32 info, enabled;

    /* Read L1D cache info registers */
    info                        = Mcal_CacheP_getCacheLevelInfo(0);
    mcal_gCacheL1dCacheLineSize = 4 << ((info & 0x7) + 2);

    /* Read L1P cache info registers for ROV */
    info                        = Mcal_CacheP_getCacheLevelInfo(1);
    mcal_gCacheL1pCacheLineSize = 4 << ((info & 0x7) + 2);

    enabled = Mcal_CacheP_getEnabled();

    /* disable the caches if anything is currently enabled */
    if (enabled)
    {
        Mcal_CacheP_disable(Mcal_CacheP_TYPE_ALL);
    }

    /* set DLFO, this is not needed on SOC AM64x and later SOCs */
    /* Mcal_CacheP_setDLFO(); */

    if (mcal_gCacheConfig.enable)
    {
        Mcal_CacheP_configForceWrThru(mcal_gCacheConfig.enableForceWrThru);

        /*
         * Mcal_CacheP_enable() code will invalidate the L1D and L1P caches.
         * Therefore, no need to explicitly invalidate the cache here.
         */
        Mcal_CacheP_enable(Mcal_CacheP_TYPE_ALL);
    }
}

void CACHE_SECTION Mcal_CacheP_disable(uint32 type)
{
    uint32 enabled;

    /* only disable caches that are currently enabled */
    enabled = Mcal_CacheP_getEnabled();

    if (enabled & (type & Mcal_CacheP_TYPE_L1D))
    {
        AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
        Mcal_CacheP_disableL1d(); /* Disable L1D Cache */
        AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
    }
    if (enabled & (type & Mcal_CacheP_TYPE_L1P))
    {
        AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
        Mcal_CacheP_disableL1p(); /* Disable L1P Cache */
        AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
    }
}

void CACHE_SECTION Mcal_CacheP_enable(uint32 type)
{
    uint32 disabled;

    /* only enable caches that are currently disabled */
    disabled = ~(Mcal_CacheP_getEnabled());

    if (disabled & (type & Mcal_CacheP_TYPE_L1D))
    {
        Mcal_CacheP_enableL1d(); /* Enable L1D Cache */
    }
    if (disabled & (type & Mcal_CacheP_TYPE_L1P))
    {
        Mcal_CacheP_enableL1p(); /* Enable L1P Cache */
    }
}

void CACHE_SECTION Mcal_CacheP_inv(void *blockPtr, uint32 byteCnt, uint32 type)
{
    if (type & Mcal_CacheP_TYPE_L1P)
    {
        Mcal_CacheP_invL1p((uint32)blockPtr, byteCnt);
    }
    if (((type) & ((uint32)Mcal_CacheP_TYPE_L1D)) != 0U)
    {
        Mcal_CacheP_invL1d((uint32)blockPtr, byteCnt);
    }
}
/* =========================Function separator========================= */

/* FUNCTION DEF: void Mcal_CacheP_configForceWrThru(uint32 enable) */
asm(".global Mcal_CacheP_configForceWrThru         ");
asm(".type Mcal_CacheP_configForceWrThru,%function ");
asm(".arm                                     ");
asm(".align 2 ");
asm("Mcal_CacheP_configForceWrThru:");
asm("mrc     p15, #0, r1, c1, c0, #1");  // fetch Auxiliary Ctrl Register into r1
asm("cmp     r0, #0                 ");
asm("beq     FWT_disable            ");
asm("orr     r1, r1, #(1 << 9)      ");  // set (enable) force write-thru bit
asm("b       FWT_exit               ");

asm("FWT_disable:");
asm("bic     r1, r1, #(1 << 9) ");  // clear (disable) force write-thru bit

asm("FWT_exit:");
asm("mcr     p15, #0, r1, c1, c0, #1");  // write Auxiliary Ctrl Register
asm("bx      lr");

/* =========================Function separator========================= */
/* FUNCTION DEF: void Mcal_CacheP_invL1p(uint32 blockPtr, uint32 byteCnt)
 *
 *       r0 - contains blockPtr
 *       r1 - contains byteCnt
 */
asm(".global Mcal_CacheP_invL1p         ");
asm(".type Mcal_CacheP_invL1p,%function ");
asm(".arm                          ");
asm(".align 2                      ");
asm("Mcal_CacheP_invL1p:");
asm("push    {r4}                      ");
asm("add     r1, r0, r1                ");  // calculate last address
asm("ldr     r3, l1pCacheLineSizeAddr  ");
asm("ldr     r3, [r3]                  ");
asm("sub     r4, r3, #1                ");
asm("bic     r0, r0, r4                ");  // align blockPtr to cache line
asm("invL1pCache_loop:");
asm("mcr     p15, #0, r0, c7, c5, #1 ");  // invalidate single entry in ICache
asm("add     r0, r0, r3              ");  // increment address by cache line size
asm("cmp     r0, r1                  ");  // compare to last address
asm("blo     invL1pCache_loop        ");  // loop if > 0
asm("dsb                             ");  // drain write buffer
asm("isb                             ");  // flush instruction pipeline
asm("pop     {r4}                    ");
asm("bx      lr                      ");

asm("l1pCacheLineSizeAddr:  .word   mcal_gCacheL1pCacheLineSize");

/* =========================Function separator========================= */
/* FUNCTION DEF: void Mcal_CacheP_enableL1p(void) */
asm(".global Mcal_CacheP_enableL1p               ");
asm(".type Mcal_CacheP_enableL1p,%function       ");
asm(".arm                                   ");
asm(".align 2                               ");
asm("Mcal_CacheP_enableL1p:");
asm("mrc     p15, #0, r0, c1, c0, #0 ");
asm("orr     r0, r0, #0x1000         ");
asm("mcr     p15, #0, r1, c7, c5, #0 ");
asm("mcr     p15, #0, r0, c1, c0, #0 ");
asm("isb                             ");
asm("bx      lr                      ");
/* =========================Function separator========================= */
/* FUNCTION DEF: void Mcal_CacheP_enableL1d(void) */
asm(".global Mcal_CacheP_enableL1d          ");
asm(".type Mcal_CacheP_enableL1d,%function  ");
asm(".arm                              ");
asm(".align 2                          ");
asm("Mcal_CacheP_enableL1d:");
asm("mrc     p15, #0, r0, c1, c0, #0 ");  // read SCR register
asm("orr     r0, r0, #0x0004         ");  // set C bit (bit 2) to 1
asm("dsb                             ");
asm("mcr     p15, #0, r1, c15, c5, #0");  // Invalidate entire data cache
asm("mcr     p15, #0, r0, c1, c0, #0 ");  // L1D cache enabled
asm("bx      lr                      ");
/* =========================Function separator========================= */
/* FUNCTION DEF: void Mcal_CacheP_disableL1p(void) */
asm(".global Mcal_CacheP_disableL1p         ");
asm(".type Mcal_CacheP_disableL1p,%function ");
asm(".arm                              ");
asm(".align 2                          ");
asm("Mcal_CacheP_disableL1p:");
asm("mrc     p15, #0, r0, c1, c0, #0");
asm("bic     r0, r0, #0x1000        ");
asm("mcr     p15, #0, r0, c1, c0, #0");
asm("mcr     p15, #0, r1, c7, c5, #0");
asm("isb                            ");
asm("bx      lr                     ");

/* =========================Function separator========================= */

/* FUNCTION DEF: void Mcal_CacheP_wbInvAllAsm()
 *
 * Write back and invalidate entire data cache
 */
asm(".global Mcal_CacheP_wbInvAllAsm");
asm(".type Mcal_CacheP_wbInvAllAsm,%function");
asm(".arm");
asm(".align 2");
asm("Mcal_CacheP_wbInvAllAsm:");
asm("dmb ");                             // Ensure all previous memory accesses
                                         // complete
asm("mrc     p15, #1, r0, c0, c0, #1");  // read clidr
asm("ands    r3, r0, #0x7000000    ");   // extract loc from clidr
asm("mov     r3, r3, lsr #23       ");   // left align loc bit field
asm("beq     finished              ");   // if loc is 0, then no need to clean

asm("mov     r10, #0            ");  // start clean at cache level 0

asm("loop1:");
asm("add     r2, r10, r10, lsr #1");  // work out 3x current cache level
asm("mov     r1, r0, lsr r2      ");  // extract cache type bits from clidr
asm("and     r1, r1, #7          ");  // mask of bits for current cache only
asm("cmp     r1, #2              ");  // see what cache we have at this level
asm("blt     skip                ");  // skip if no cache, or just i-cache

asm("mrs     r6, cpsr ");
asm("cpsid   i          ");               // disable interrupts
asm("mcr     p15, #2, r10, c0, c0, #0");  // select current cache level in cssr
asm("isb                             ");  // flush prefetch buffer
asm("mrc     p15, #1, r1, c0, c0, #0 ");  // read the new csidr
asm("msr     cpsr_c, r6              ");  // restore interrupts

asm("and     r2, r1, #7          ");  // extract the length of the cache lines
asm("add     r2, r2, #4          ");  // add 4 (line length offset)
asm("mov     r4, #0x3ff          ");
asm("ands    r4, r4, r1, lsr #3  ");  // find maximum number on the way size
asm("clz     r5, r4              ");  // find bit position of way size inc.
asm("mov     r7, #0x7fff         ");
asm("ands    r7, r7, r1, lsr #13 ");  // extract max number of the index size
asm("loop2:");
asm("mov     r9, r4  ");  // create working copy of max way size
asm("loop3:");
asm("orr     r11, r10, r9, lsl r5 ");       // factor way and cache number into r11
asm("orr     r11, r11, r7, lsl r2 ");       // factor index number into r11
asm("mcr     p15, #0, r11, c7, c14, #2 ");  // clean & invalidate by set/way
asm("subs    r9, r9, #1            ");      // decrement the way
asm("bge     loop3                 ");
asm("subs    r7, r7, #1            ");  // decrement the index
asm("bge     loop2                 ");
asm("skip:");
asm("add     r10, r10, #2    ");  // increment cache number
asm("cmp     r3, r10");
asm("bgt     loop1");
asm("finished:");
asm("mov     r10, #0                 ");  // swith back to cache level 0
asm("mcr     p15, #2, r10, c0, c0, #0");  // select current cache level in cssr
asm("dsb                             ");
asm("isb                             ");  // flush prefetch buffer
asm("bx      lr                      ");
/* =========================Function separator========================= */
/* FUNCTION DEF: void Mcal_CacheP_disableL1d(void) */
asm(".global Mcal_CacheP_disableL1d        ");
asm(".type Mcal_CacheP_disableL1d,%function");
asm(".arm                             ");
asm(".align 2                         ");
asm("Mcal_CacheP_disableL1d:");
asm("push    {r0-r7, r9-r11, lr}            ");
asm("mrc     p15, #0, r0, c1, c0, #0        ");
asm("bic     r0, r0, #0x0004                ");
asm("dsb                                    ");
asm("mcr     p15, #0, r0, c1, c0, #0        ");
asm("movw    r0, :lower16:Mcal_CacheP_wbInvAllAsm");
asm("movt    r0, :upper16:Mcal_CacheP_wbInvAllAsm");
asm("blx     r0                             ");
asm("pop     {r0-r7, r9-r11, lr}            ");
asm("bx      lr                             ");

/* =========================Function separator========================= */
asm(".global Mcal_CacheP_getEnabled         ");
asm(".type Mcal_CacheP_getEnabled,%function ");
asm(".arm                              ");
asm(".align 2                          ");
asm("Mcal_CacheP_getEnabled:");
asm("mov     r0, #0");                   // Do L1 first
asm("mrc     p15, #0, r1, c1, c0, #0");  // fetch Control Register into r1
asm("tst     r1, #0x1000 ");             // test I bit (bit 12) for L1P
asm("addne   r0, r0, #1  ");             // if I is true, L1P is enabled
asm("tst     r1, #0x0004 ");             // test C bit (bit 2) for L1D
asm("addne   r0, r0, #2  ");             // if C bit is true, L1D is enabled
                                         // Do L2 next
asm("mrc     p15, #0, r1, c1, c0, #1");  // fetch Auxiliary Ctrl Register into r1
asm("tst     r1, #0x0002            ");  // test L2EN bit (bit 1) for L2EN
asm("beq     getEnabledDone         ");
asm("tst     r0, #0x0001            ");
asm("addne   r0, r0, #4             ");  // If L2EN and L1P then L2P
asm("tst     r0, #0x0002            ");
asm("addne   r0, r0, #8             ");  // If L2EN and L1D then L2D

asm("getEnabledDone:");
asm("bx      lr");

/* =========================Function separator========================= */
/* FUNCTION DEF: uint32 Mcal_CacheP_getCacheLevelInfo(uint32 level) */
asm(".global Mcal_CacheP_getCacheLevelInfo         ");
asm(".type Mcal_CacheP_getCacheLevelInfo,%function ");
asm(".arm                                     ");
asm(".align 2                                 ");
asm("Mcal_CacheP_getCacheLevelInfo:");
asm("mcr     p15, #2, r0, c0, c0, #0 ");  // write to Cache Size Selection Reg
asm("mrc     p15, #1, r0, c0, c0, #0 ");  // read Cache Size Id Reg
asm("bx      lr                      ");

/* =========================Function separator========================= */
/* FUNCTION DEF: void Mcal_CacheP_wb(void *addr, uint32 size, uint32 type)
 * Writes back the range of MVA in data cache. First, wait on any previous cache
 * operation.
 *
 *       r0 - contains blockPtr
 *       r1 - contains byteCnt
 *       r2 - contains bit mask of cache type (unused)
 */
asm(".global Mcal_CacheP_wb");
asm(".type Mcal_CacheP_wb,%function");
asm(".arm");
asm("Mcal_CacheP_wb:");
asm("push    {r4, r5}");
asm("dmb");
asm("add     r1, r0, r1");  // calculate last address
asm("ldr     r4, l1dCacheLineSizeWbAddr");
asm("ldr     r4, [r4]");
asm("sub     r5, r4, #1");
asm("bic     r0, r0, r5");  // align blockPtr to cache line
asm("writeback:");
asm("mcr     p15, #0, r0, c7, c14, #1");  // invalidate single entry in L1D cache
asm("add     r0, r0, r4  ");              // increment address by cache line size
asm("cmp     r0, r1");                    // compare to last address
asm("blo     writeback");                 // loop if > 0
asm("dsb");                               // drain write buffer
asm("pop     {r4, r5}");
asm("bx      lr");  // return

asm("l1dCacheLineSizeWbAddr	: .long  mcal_gCacheL1dCacheLineSize");

/* =========================Function separator========================= */

/* FUNCTION DEF: void Mcal_CacheP_wbInv(void *addr, uint32 size, uint32 type)
 *
 * Writes back and invalidates the range of MVA in data cache.
 * First, wait on any previous cache operation.
 *
 *       r0 - contains blockPtr
 *       r1 - contains byteCnt
 *       r2 - contains bitmask of cache type (unused)
 */
asm(".global Mcal_CacheP_wbInv");
asm(".type Mcal_CacheP_wbInv,%function");
// asm(".section".text.cache","ax",%progbits");
asm(".arm");
asm("Mcal_CacheP_wbInv:");
asm("push    {r4, r5}");
asm("dmb");                 // Ensure all previous memory accesses complete
asm("add     r1, r0, r1");  // calculate last address
asm("ldr     r4, l1dCacheLineSizeWbInvAddr");
asm("ldr     r4, [r4]");
asm("sub     r5, r4, #1");
asm("bic     r0, r0, r5");  // align blockPtr to cache line
asm("writebackInv:");
asm("mcr     p15, #0, r0, c7, c14, #1");  // writeback inv a cache line
asm("add     r0, r0, r4");                // increment address by cache line size
asm("cmp     r0, r1");                    // compare to last address
asm(" blo     writebackInv");             // loop if count > 0
asm("dsb");                               // drain write buffer
asm("pop     {r4, r5}");
asm("bx      lr");

asm("l1dCacheLineSizeWbInvAddr: .long mcal_gCacheL1dCacheLineSize");

/* =========================Function separator========================= */

/* FUNCTION DEF: void Mcal_CacheP_invL1d(uint32 blockPtr, uint32 byteCnt)
 *
 *       r0 - contains blockPtr
 *       r1 - contains byteCnt
 */
asm(".global Mcal_CacheP_invL1d");
asm(".type Mcal_CacheP_invL1d,%function");
asm(".arm");
asm("Mcal_CacheP_invL1d:");
asm("push    {r4}");
asm("add     r1, r0, r1");  // calculate last address
asm("ldr     r3, l1dCacheLineSizeInvL1dAddr");
asm("ldr     r3, [r3]");
asm("sub     r4, r3, #1");
asm("bic     r0, r0, r4");  // align blockPtr to cache line
asm("invL1dCache_loop:");
asm("mcr     p15, #0, r0, c7, c6, #1");  // writeback inv a cache line
asm("add     r0, r0, r3");               // increment address by cache line size
asm("cmp     r0, r1");                   // compare to last address
asm(" blo     invL1dCache_loop");        // loop if count > 0
asm("dsb");                              // drain write buffer
asm("pop     {r4}");
asm("bx      lr");

asm("l1dCacheLineSizeInvL1dAddr: .long mcal_gCacheL1dCacheLineSize");
