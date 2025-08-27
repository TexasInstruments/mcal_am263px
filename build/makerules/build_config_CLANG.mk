#*******************************************************************************
#                                                                              *
# Copyright (c) 2022 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# Filename: build_config.mk
#
# Build configuration make file - This file contains all the options that are
#                                 frequently changed
#
# This file changes when:
#     1. format needs to change (eg: COFF/ELF)
#     2. Endian-ness needs to change (little/big)
#     3. global compiler and linker options need to change (one entry for each
#                                                           core)
#     4. Profile needs to change (debug/release/prod_release)
#

# Global options

# Build - Allowed values = full | xdc | make
#         This "builds" packages based on the setting:
#                 full - build both XDC and make (all the packages/components)
#                 xdc  - build and configure only XDC packages
#                 make - build only make based components and link everything
# NOTE: BUILD need not be defined at all, which case it behaves like it is set
#       to "full". This is to ensure backward compatibility.
BUILD = full

# Endianness : Allowed values = little | big
ENDIAN = little

# Format : Allowed values = COFF | ELF
FORMAT = ELF

# r5f - (Cortex-R5)
CFLAGS_GLOBAL_r5f = -mthumb -g -fdiagnostics-show-option \
                  -ffunction-sections -fshort-enums

LNKFLAGS_GLOBAL_r5f = -Wl,-a,--rom_model,--warn_sections,--reread_libs,--unused_section_elimination=on,--compress_dwarf=on,--copy_compression=rle,--cinit_compression=rle

VFPFLAGS_GLOBAL_r5f = -mfloat-abi=hard -mfpu=vfpv3-d16 --ffp_mode=std

# Nothing beyond this point
