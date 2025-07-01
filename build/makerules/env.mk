#*******************************************************************************
#                                                                              *
# Copyright (c) 2022 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# File: env.mk. This file contains all the paths and other ENV variables

#
# Module paths
#

# Destination root directory.
#   - specify the directory where you want to place the object, archive/library,
#     binary and other generated files in a different location than source tree
#   - or leave it blank to place then in the same tree as the source
ifeq ($(BUILD_OS_TYPE),baremetal)
ifeq ($(MCAL_CONFIG),0)
  DEST_ROOT = $(mcal_PATH)/binary
else
  DEST_ROOT = $(mcal_PATH)/binary/config_$(MCAL_CONFIG)
endif
else
  DEST_ROOT = $(mcal_demo_PATH)/binary
endif

# Set path separator, etc based on the OS
ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR = ;
  UTILSPATH = $(UTILS_INSTALL_DIR)/
else
  # else, assume it is linux
  PATH_SEPARATOR = :
  UTILSPATH = /bin/
endif

# Autosar framework include files
autoSARBSW_INCLUDE = $(autosarBSWInc_PATH)

#Autosar generated files include path
autosarConfig_INCLUDE = $(autosarConfig_PATH)

include $(MAKERULEDIR)/component.mk
export autoSARBSW_INCLUDE
export autosarConfig_INCLUDE

# Commands commonly used within the make files
RM = $(UTILSPATH)rm
RMDIR = $(UTILSPATH)rm -rf
MKDIR = $(UTILSPATH)mkdir
ECHO = @$(UTILSPATH)echo

#emake provides detailed info for build analysis.
EMAKE = emake --emake-emulation=gmake --emake-gen-subbuild-db=1 --emake-annodetail=waiting

ifeq ($(OS),Windows_NT)
  MAKE = gmake
#  MAKE =  $(EMAKE)
else
  MAKE = make
endif
EGREP = $(UTILSPATH)egrep
CP = $(UTILSPATH)cp
MV = $(UTILSPATH)mv
ifeq ($(OS),Windows_NT)
  CHMOD = $(UTILSPATH)echo
else
  CHMOD = $(UTILSPATH)chmod
endif

ifeq ($(OS),Windows_NT)
  TOUCH=$(xdc_PATH)/bin/touch
else
  TOUCH=touch
endif

CONFIG_BLD_LNK_r5f   = $(pdk_PATH)/ti/build/$(SOC)/linker_r5.lds

STRIP_ALL_ARM = $(CODEGEN_PREFIX)strip -s
STRIP_DEBUG_ARM = $(CODEGEN_PREFIX)strip --strip-debug

PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_M3)/bin
PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_A15)/bin
PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_A8)/bin
PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_DSP)/bin
PATH += $(PATH_SEPARATOR)$(GMAKE_DIR)
PATH += $(PATH_SEPARATOR)$(CODEGEN_PATH_CR4)/bin
export PATH

# Nothing beyond this point
