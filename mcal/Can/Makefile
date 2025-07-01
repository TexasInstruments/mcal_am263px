MODULE_NAME = can

ifeq ($(SOC), $(filter $(SOC), am263 am273 am263px am261))
SOC_FILES = V0
endif

SRCDIR = src $(SOC_FILES)
INCDIR = include $(SRCDIR)

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = can canPriv

MODULE_SRC_BASE_PATH := $(mcal_PATH)/Can
canPriv_INCLUDE = $(mcal_PATH)/include \
                  $(mcal_PATH)/include/hw \
                  $(mcal_PATH)/include/hw/$(PLATFORM)

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += Can.c Can_Priv.c Can_Irq.c 
ifeq ($(PLATFORM), $(filter $(PLATFORM), am263 am273 am2732s am263px am261))
SRCS_$(SOCFAMILY) += mcan.c Can_Mcan.c
endif
PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCAL_CFLAGS)

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
