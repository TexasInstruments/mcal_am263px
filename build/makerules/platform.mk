#*******************************************************************************
#                                                                              *
# Copyright (c) 2022 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# Filename: platform.mk
#
# Platforms make file - Platform/SoC/targets are defined/derived in this file
#
# This file needs to change when:
#     1. a new platform/SoC is added, which also might have its own cores/ISAs
#

#
# Derive SOC from PLATFORM
#


# AM263
ifeq ($(PLATFORM),$(filter $(PLATFORM), am263))
SOC = am263
SOCFAMILY = am263
endif

# AM263P
ifeq ($(PLATFORM),$(filter $(PLATFORM), am263px))
SOC = am263px
SOCFAMILY = am263px
endif

# AM261
ifeq ($(PLATFORM),$(filter $(PLATFORM), am261))
SOC = am261
SOCFAMILY = am261
endif

# Derive Target/ISA from CORE

# r5f
ifeq ($(CORE),$(filter $(CORE), r5f0_0))
 ISA = r5f
 ARCH = armv7m
endif

#
# Derive XDC/ISA specific settings
#
ifeq ($(FORMAT),ELF)
  FORMAT_EXT = e
endif
# If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
#    in the filename extension of object/library/executable files
ifeq ($(ENDIAN),big)
  ENDIAN_EXT = e
endif

# Define the file extensions
OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)

export SOC
export SOCFAMILY
export PLATFORM

# Nothing beyond this point
