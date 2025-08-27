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

#
#
#
# r5f - (Cortex-R5)
CFLAGS_GLOBAL_r5f = --code_state=16 --abi=eabi -g --display_error_number --diag_warning=225 --diag_wrap=off \
                  --gen_func_subsections=on --enum_type=packed --auto_inline=0 --small_enum
LNKFLAGS_GLOBAL_r5f = -z -a --rom_model --warn_sections --reread_libs --unused_section_elimination=on \
                   --compress_dwarf=on --copy_compression=rle --cinit_compression=rle --reread_libs --disable_auto_rts\
                   --generate_dead_funcs_list=$(BUILD_DIR)\feedback.txt
VFPFLAGS_GLOBAL_r5f = --float_support=vfpv3d16 --fp_mode=strict

# Nothing beyond this point
