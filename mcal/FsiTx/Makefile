MODULE_NAME = fsitx

ifeq ($(SOC), $(filter $(SOC), am263 am263px am261))
SOC_FILES = V0
endif

SRCDIR = src $(SOC_FILES)
INCDIR = include $(SOC_FILES)
INCDIR = $(mcal_PATH)/include \
         $(mcal_PATH)/include/hw/$(PLATFORM) \
         $(mcal_PATH)/include/hw \
		     include src/hw include src $(SOC_FILES)\
		     $(mcal_PATH)/Dma/include $(mcal_PATH)/Dma/$(SOC_FILES)
         
# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autoSARBSW autosarConfig Dma

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = fsitx

MODULE_SRC_BASE_PATH := $(mcal_PATH)/FsiTx

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += Cdd_FsiTx.c Cdd_FsiTx_Irq.c 
SRCS_$(SOCFAMILY) += Cdd_FsiTx_Priv.c Cdd_FsiTx_Platform.c
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
