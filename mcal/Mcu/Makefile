MODULE_NAME = mcu

ifeq ($(PLATFORM),am263)
SOC_FILES = V0
endif
ifeq ($(PLATFORM), am273)
SOC_FILES = V1
endif
ifeq ($(PLATFORM), am2732s)
SOC_FILES = V1
endif
ifeq ($(PLATFORM),am263px)
SOC_FILES = V2
endif
ifeq ($(PLATFORM),am261)
SOC_FILES = V3
endif

SRCDIR = src $(SOC_FILES) $(mcal_PATH)/include/hw/$(PLATFORM)
INCDIR = $(mcal_PATH)/include \
         $(mcal_PATH)/include/hw/$(PLATFORM) \
         $(mcal_PATH)/include/hw \
         include src/hw include src $(SOC_FILES)
		 
# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = mcu
INCLUDE_INTERNAL_INTERFACES += mcuPriv

mcuPriv_INCLUDE =  $(mcal_PATH)/include \
                   $(mcal_PATH)/include/hw/$(PLATFORM) $(mcal_PATH)/include/hw

MODULE_SRC_BASE_PATH := $(mcal_PATH)/Mcu

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += Mcu.c
SRCS_$(SOCFAMILY) += Mcu_Priv.c Mcal_Libs_Utils.c
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
