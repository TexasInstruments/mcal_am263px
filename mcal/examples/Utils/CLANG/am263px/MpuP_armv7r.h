#ifndef MPUP_ARMV7_H_
#define MPUP_ARMV7_H_

#include "Platform_Types.h"
#include "Std_Types.h"
#include "assert.h"

#define MPU_SECTION __attribute__((section(".text.mpu")))
/**
 * \brief Enum's to represent different types of access permissions that are possible for a given
 * MPU region
 */
typedef enum MpuP_AccessPerm_
{
    MpuP_AP_ALL_BLOCK = (0x0u), /**< All accesses are blocked */
    MpuP_AP_S_RW      = (0x1u), /**< Only RD+WR supervisor mode accesses are allowed  */
    MpuP_AP_S_RW_U_R  = (0x2u), /**< RD+WR supervisor and RD only user mode accesses are allowed  */
    MpuP_AP_ALL_RW    = (0x3u), /**< All RD+WR accesses are allowed */
    MpuP_AP_S_R       = (0x5u), /**< Only RD supervisor mode accesses are allowed */
    MpuP_AP_ALL_R     = (0x6u)  /**< All RD accesses are allowed */
} MpuP_AccessPerm;

/**
 * \brief Enum's to represent different possible MPU region size
 */
typedef enum MpuP_RegionSize_
{
    MpuP_RegionSize_32 = 0x4,
    MpuP_RegionSize_64,
    MpuP_RegionSize_128,
    MpuP_RegionSize_256,
    MpuP_RegionSize_512,
    MpuP_RegionSize_1K,
    MpuP_RegionSize_2K,
    MpuP_RegionSize_4K,
    MpuP_RegionSize_8K,
    MpuP_RegionSize_16K,
    MpuP_RegionSize_32K,
    MpuP_RegionSize_64K,
    MpuP_RegionSize_128K,
    MpuP_RegionSize_256K,
    MpuP_RegionSize_512K,
    MpuP_RegionSize_1M,
    MpuP_RegionSize_2M,
    MpuP_RegionSize_4M,
    MpuP_RegionSize_8M,
    MpuP_RegionSize_16M,
    MpuP_RegionSize_32M,
    MpuP_RegionSize_64M,
    MpuP_RegionSize_128M,
    MpuP_RegionSize_256M,
    MpuP_RegionSize_512M,
    MpuP_RegionSize_1G,
    MpuP_RegionSize_2G,
    MpuP_RegionSize_4G
} MpuP_RegionSize;

/**
 * \brief Attribute's to apply for a MPU region
 *
 * \note Refer to ARMv7-R or ARMv7-M architecture manual for more details
 *
 * \note C, B, S, TEX[0:2] bits
 *   together control if a region should be fully cached or non-cached or marked as device memory
 */
typedef struct MpuP_RegionAttrs_
{
    uint8 isEnable;             /**< 1: enable this region, 0: disable this region */
    uint8 isCacheable;          /**< 1: set C bit, 0: clear C bit */
    uint8 isBufferable;         /**< 1: set B bit, 0: clear B bit */
    uint8 isSharable;           /**< 1: set S bit, 0: clear S bit */
    uint8 isExecuteNever;       /**< 1: set XN bit, 0: clear XN bit */
    uint8 tex;                  /**< set TEX[0:2] bits */
    uint8 accessPerm;           /**< set AP[0:2] bits, see \ref MpuP_AccessPerm */
    uint8 subregionDisableMask; /**< subregion disable mask, bitN = 1 means disable that subregion */
} MpuP_RegionAttrs;

/**
 * \brief Region config structure, this used by SysConfig and not to be used by end-users directly
 */
typedef struct MpuP_RegionConfig_
{
    uint32           baseAddr; /**< region start address, MUST aligned to region size */
    uint32           size;     /**< region size, see \ref MpuP_RegionSize */
    MpuP_RegionAttrs attrs;    /** region attributes, see \ref MpuP_RegionAttrs */

} MpuP_RegionConfig;

/**
 * \brief MPU config structure, this used by SysConfig and not to be used by end-users directly
 */
typedef struct MpuP_Config_
{
    uint32 numRegions;             /** Number of regions to configure */
    uint32 enableBackgroundRegion; /**< 0: disable backgroun region, 1: enable background region */
    uint32 enableMpu;              /**< 0: keep MPU disabled, 1: enable MPU */

} MpuP_Config;

void MPU_SECTION MpuP_init(void);
void MPU_SECTION MpuP_disable(void);
void MPU_SECTION MpuP_enable(void);

#endif /*MPU_H_*/
